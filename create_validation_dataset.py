# TODO: This file takes the timeseries of each household and runs the simulation for each household until the heating
#  timeseries fits well to the actual results. Thus it goes through the building types and adds insulation. It also
#  needs to check setpoints for heating and cooling.
import os
import validation.functions as f
import pandas as pd
import tqdm
from hts import Hts
from pprint import pprint
from geopy.geocoders import Nominatim
import time
import sys

ELEVATIONS = {
    'G2001690': 374,
    'G2700270': 1020,
    'G2800730': 52,
    'G3500090': 1301,
    'G4100070': 7,
    'G4802650': 606,
    'G5500950': 276,
}


def get_elevation(latitude, longitude, county_id):
    geolocator = Nominatim(user_agent="my_app")
    location = geolocator.reverse(f"{latitude}, {longitude}")

    elevation = location.raw.get('address').get('ele')
    if elevation is None:
        elevation = ELEVATIONS.get(county_id, None)
    else:
        pass
        # print(elevation, ELEVATIONS[county_id])

    return elevation


def get_config_params(config: dict, info: dict, county_id: str):
    """Extracts all config parameters from the general info file and returns an updated config dict"""

    # Building
    config['building']['year'] = 1918
    config['building']['floors'] = int(info['in.geometry_stories'])
    config['building']['area'] = round(f.sqft2sqm(info['in.sqft']))
    config['building']['occupants'] = int(info['in.occupants'])

    # Heating
    config['heating']['system'] = 'high-temp'
    setpoint = int(info['in.heating_setpoint'][:-1])
    config['heating']['setpoint'] = round(f.f2c(setpoint), 1)
    # Note: Some of the households also have offsets for heating and cooling for times of the day.
    #       Check if this has any influence.

    # Cooling
    setpoint = int(info['in.cooling_setpoint'][:-1])
    config['cooling']['setpoint'] = round(f.f2c(setpoint), 1)
    # Ensure that the cooling setpoint is higher than the heating setpoint
    if config['cooling']['setpoint'] <= config['heating']['setpoint']:
        config['cooling']['setpoint'] = config['heating']['setpoint'] + 0.5

    # Operation
    config['operation']['occupancy'] = True
    config['operation']['electricity'] = True

    # Environment
    config['environment']['elevation'] = get_elevation(info['in.weather_file_latitude'],
                                                       info['in.weather_file_longitude'],
                                                       county_id)
    config['environment']['latitude'] = info['in.weather_file_latitude']
    config['environment']['longitude'] = info['in.weather_file_longitude']

    return config


def format_weather(county:str, county_id:str):

    # Try to load already adjusted weather file, otherwise create it
    try:
        weather = pd.read_csv(f'./validation/counties/{county}/weather/{county_id}_2018_adjusted.csv')
    except FileNotFoundError:
        # Load weather data
        weather = pd.read_csv(f'./validation/counties/{county}/weather/{county_id}_2018.csv',
                              index_col='date_time', parse_dates=True)
        weather.index -= pd.Timedelta(hours=1)  # subtract 1 hour to get the start of the interval
        weather = weather.resample('15min').interpolate()  # resample to 15 minutes

        # Add 3 more rows as they are missing when resampling
        last_row = weather.iloc[-1]  # Get the last row

        # Create new timestamps for the additional rows
        new_timestamps = pd.date_range(start=last_row.name, freq='15min', periods=4)[1:]

        # Create new rows with the specified timestamps
        new_rows = pd.DataFrame([last_row] * 3, index=new_timestamps)

        # Concatenate the new rows with the original DataFrame
        weather = pd.concat([weather, new_rows])

        # Adjust weather column names to hts format
        weather = weather.rename(columns={'Dry Bulb Temperature [°C]': 'temp',
                                          'Relative Humidity [%]': 'humidity',
                                          'Wind Speed [m/s]': 'wind_speed',
                                          'Wind Direction [Deg]': 'wind_dir',
                                          'Global Horizontal Radiation [W/m2]': 'ghi',
                                          'Diffuse Horizontal Radiation [W/m2]': 'dhi', })

        # Drop unnecessary columns
        weather = weather.drop(columns='Direct Normal Radiation [W/m2]')

        # Convert temperature from Celsius to Kelvin
        weather['temp'] += 273.15

        # Convert timestamps to unix timestamps
        weather.index = weather.index.astype('int64') / 10 ** 9

        # Rename index
        weather.index.name = 'timestamp'

        # Adjust the dtypes
        weather.index = weather.index.astype(int)
        weather['temp'] = weather['temp'].round(2).astype(float)
        weather['humidity'] = weather['humidity'].round(0).astype(int)
        weather['wind_speed'] = weather['wind_speed'].round(2).astype(float)
        weather['wind_dir'] = weather['wind_dir'].round(0).astype(int)
        weather['ghi'] = weather['ghi'].round(0).astype(int)
        weather['dhi'] = weather['dhi'].round(0).astype(int)

        # Save new weather file
        weather.to_csv(f'./validation/counties/{county}/weather/{county_id}_2018_adjusted.csv')

    return weather

# TODO: Issue seems to be that households do not return the correct results --> talk to Daniel
# Issue 1: Once another round is simulated, the results are not correct anymore.
# Issue 2: Cooling is higher than expected. --> Talk to Daniel
# Also check if heating adjusted makes sense or if heating_orig should be used instead
def main():
    # Go through each county
    county_path = os.path.abspath('./validation/counties')
    pbar_counties = tqdm.tqdm(os.listdir(county_path), desc='Counties', position=0, leave=False)
    for county in pbar_counties:
        # Set the progressbar description
        pbar_counties.set_description(f'County: {county}')

        # Get county ID
        county_id = county.split('_')[0]

        # Load the county metadata
        metadata = f.load_file(os.path.join(county_path, county, f'{county_id}_metadata.csv'))

        # Load the household files
        path = f'./validation/counties/{county}/households'
        path = os.path.abspath(path)
        households = next(os.walk(path))[1]

        weather = format_weather(county=county, county_id=county_id)

        # Loop through households
        pbar_households = tqdm.tqdm(households, desc='Households', position=1, leave=False)
        for household in pbar_households:

            # Load the timeseries file
            try:
                power = pd.read_csv(os.path.join(path, household, f'{household}_timeseries_adjusted.csv'))
            except FileNotFoundError:
                print(f'Power file of household {household} in county {county} not found. Skipping household...')
                continue

            # Format it accordingly
            power['timestamp'] = pd.to_datetime(power['timestamp'])
            power['timestamp'] = power['timestamp'].astype('int64') / 10 ** 9
            power['timestamp'] = power['timestamp'].astype(int)
            src_orig = power.copy()  # original power file with updated timestamps
            power = power.drop(columns=['heating', 'cooling', 'hp', 'temp_heat', 'temp_diff', 'cop', 'heating_orig'])

            # Load standard config file and adjust settings
            config_old = f.load_file('./input.yml')
            info = metadata.loc[int(household)]
            config_old = get_config_params(config=config_old, info=info, county_id=county_id)

            # Note: The parameters to decide which result is best need to be adjusted once cooling becomes a part of it
            years = [1919, 1949, 1958, 1969, 1979, 1984, 1995, 2002, 2009, 2016]
            systems = ['high-temp', 'high-temp', 'high-temp', 'high-temp',  # 1919-1978
                       'mid-temp', 'mid-temp', 'mid-temp', 'mid-temp',      # 1979-2008
                       'low-temp', 'low-temp']                              # 2009-2016

            # Retrieve heating power from the original power file
            power_heat = round(src_orig['heating'].max() / 1e3 + 5)  # Heating power in kW
            config_old['heating']['power'] = power_heat
            config_new = config_old.copy()  # contains the config of the newer simulation (as always two are stored)

            # config_old['building']['year'] = 2016
            #
            # print()
            # print(config_old)

            # Dict to store the results
            results = {
                'older': None,      # previous results
                'older_ins': None,  # previous results with insulation
                'older_ins_newer': None,  # previous results with insulation and newer config
                'newer': None,      # newer results
            }
            # Set the progressbar description
            year = config_old['building']['year']
            pbar_households.set_description(f'Household: {household}: {year}')
            print()
            print('Original')
            print(f'Heating: {src_orig["heating"].sum() * 0.25 / 1e6} MWh')
            print(f'Cooling: {src_orig["cooling"].sum() * 0.25 / 1e6} MWh')

            # for i in range(3):

            # Calculate the results for the first setup (1918)
            hts = Hts(config=config_old,
                      weather=weather,
                      power=power)
            hts.run_simulation(silent=True, log=7)
            df = hts.save_results(path=os.path.join(path, household, f'{household}_sim_{year}_pycharm.csv'))
            results['older'] = df

            print()
            # print(i)
            print(year)
            print(f'Heating: {df["heat_power"].sum() * 0.25 / 1e6} MWh')
            print(f'Cooling: {df["cool_power"].sum() * 0.25 / 1e6} MWh')

            # print('The issue seems to be in having multiple instances of a model open. It does not close the previous one.')
            #
            exit()

            # Check if results is already lower than the actual demand
            if ((df['heat_power'].sum() + df['cool_power'].sum())
                    < (src_orig['heating'].sum() + src_orig['cooling'].sum())):
                # No need to look further as the demand is already lower
                # print("Demand lower than actual demand?:")
                # print(f"1918: {((df['heat_power'].sum() + df['cool_power'].sum()) < (src_orig['heating'].sum() + src_orig['cooling'].sum()))}")
                pass
            else:
                # Loop through the years and thus improve the building envelope
                for year in years:
                    # Set the progressbar description
                    pbar_households.set_description(f'Household: {household}: {year}')

                    # Update config_new
                    config_new['building']['year'] = year
                    config_new['heating']['system'] = systems[years.index(year)]

                    # print()
                    # print(config_new)

                    # Run simulation for the new config
                    hts = Hts(config=config_new,
                              weather=weather,
                              power=power)
                    hts.run_simulation(silent=True)
                    df = hts.save_results(path=os.path.join(path, household, f'{household}_sim_{year}.csv'))
                    results['newer'] = df

                    # print()
                    # print(year)
                    # print(f'Heating: {df["heat_power"].sum() * 0.25 / 1e6} MWh')
                    # print(f'Cooling: {df["cool_power"].sum() * 0.25 / 1e6} MWh')
                    # exit()

                    # Check if the demand is lower than the actual demand and break if it is
                    if ((df['heat_power'].sum() + df['cool_power'].sum())
                            <= (src_orig['heating'].sum() + src_orig['cooling'].sum())):
                        print("Demand lower than actual demand?:")
                        print(f"{year}: {((df['heat_power'].sum() + df['cool_power'].sum()) < (src_orig['heating'].sum() + src_orig['cooling'].sum()))}")
                        break
                    else:
                        # Set config_old to config_new
                        config_old = config_new.copy()

                        # Save the results of the older simulation
                        results['older'] = df

            # Add insulation to the older config
            insulation = 5  # cm
            config_ins = config_old.copy()
            config_ins_newer = config_ins.copy()

            # Update the progressbar description
            pbar_households.set_description(f'Household: {household}: {year} -  {insulation} cm')

            # Calculate the results for the first setup (5 cm insulation)
            hts = Hts(config=config_ins,
                      weather=weather,
                      power=power)
            hts.run_simulation(silent=True)
            df = hts.save_results(path=os.path.join(path, household, f'{household}_sim_{year}_ins_{insulation}.csv'))
            results['older_ins'] = df

            # Check if results is already lower than the actual demand
            if ((df['heat_power'].sum() + df['cool_power'].sum())
                    < (src_orig['heating'].sum() + src_orig['cooling'].sum())):
                # No need to look further as the demand is already lower
                print("Demand lower than actual demand?:")
                print(f"{insulation}: {((df['heat_power'].sum() + df['cool_power'].sum()) < (src_orig['heating'].sum() + src_orig['cooling'].sum()))}")
                pass
            else:
                while True:
                    # Increase insulation by 5 cm
                    insulation += 5

                    # Add insulation
                    config_ins_newer['insulation']['roof'] = insulation
                    config_ins_newer['insulation']['wall'] = insulation
                    config_ins_newer['insulation']['floor'] = insulation

                    # Update the progressbar description
                    pbar_households.set_description(f'Household: {household}: {year} -  {insulation} cm')

                    # Run simulation
                    hts = Hts(config=config_ins,
                              weather=weather,
                              power=power)
                    hts.run_simulation(silent=True)
                    df = hts.save_results(path=os.path.join(path, household, f'{household}_sim_{year}_ins_{insulation}.csv'))
                    results['older_ins_newer'] = df

                    # Check if the demand is lower than the actual demand and break if it is
                    if ((df['heat_power'].sum() + df['cool_power'].sum())
                            <= (src_orig['heating'].sum() + src_orig['cooling'].sum())):
                        break
                    else:
                        # Set config_ins to config_ins_newer
                        config_ins = config_ins_newer.copy()

                        # Save the results of the older simulation with insulation
                        results['older_ins'] = df

                    # Check if the insulation is already 30 cm (not reasonable to go higher)
                    if insulation >= 30:
                        break

            # Calculate the difference between the actual demand and the simulated demand for each result
            diffs = {}
            for key, result in results.items():
                df = results[result]
                if df is None:
                    continue
                else:
                    # Calculate the absolute difference between the actual demand and the simulated demand
                    diff = abs(df['heat_power'].sum() + df['cool_power'].sum()) \
                           - (src_orig['heating'].sum() + src_orig['cooling'].sum())

                    # Save difference
                    diffs[key] = diff

            # Get the key with the lowest difference
            best_key = min(diffs, key=diffs.get)
            print(best_key)

            # Get the best results and config
            df = results[best_key]
            match best_key:
                case 'older':
                    config = config_old
                case 'older_ins':
                    config = config_ins
                case 'older_ins_newer':
                    config = config_ins_newer
                case 'newer':
                    config = config_new

            # Save adjusted config file
            f.save_file(os.path.abspath(os.path.join(path, household, f'{household}_config.yml')), config)

            # Save results
            df.to_csv(os.path.join(path, household, f'{household}_sim.csv'))


if __name__ == '__main__':
    raise Warning('This step was moved to run_v.py. Move on to combine_results.py')
    main()
