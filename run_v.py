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


def main(county, household, year):
    # Path to the counties
    county_path = os.path.abspath('./validation/counties')

    # Get county ID
    county_id = county.split('_')[0]

    # Load the county metadata
    metadata = f.load_file(os.path.join(county_path, county, f'{county_id}_metadata.csv'))

    # Load the household files
    path = f'./validation/counties/{county}/households'
    path = os.path.abspath(path)
    weather = format_weather(county=county, county_id=county_id)

    # Load the timeseries file
    try:
        power = pd.read_csv(os.path.join(path, household, f'{household}_timeseries_adjusted.csv'))
    except FileNotFoundError:
        print(f'Power file of household {household} in county {county} not found. Skipping household...')
        return 1

    # Format it accordingly
    power['timestamp'] = pd.to_datetime(power['timestamp'])
    power['timestamp'] = power['timestamp'].astype('int64') / 10 ** 9
    power['timestamp'] = power['timestamp'].astype(int)
    src_orig = power.copy()  # original power file with updated timestamps
    power = power.drop(columns=['heating', 'cooling', 'hp', 'temp_heat', 'temp_diff', 'cop', 'heating_orig'])

    # Load standard config file and adjust settings
    config = f.load_file('./input.yml')
    info = metadata.loc[int(household)]
    config = get_config_params(config=config, info=info, county_id=county_id)

    # Note: The parameters to decide which result is best need to be adjusted once cooling becomes a part of it
    years = [1918, 1919, 1949, 1958, 1969, 1979, 1984, 1995, 2002, 2009, 2016]
    systems = ['high-temp', 'high-temp', 'high-temp', 'high-temp', 'high-temp',     # 1918-1978
               'mid-temp', 'mid-temp', 'mid-temp', 'mid-temp',                      # 1979-2008
               'low-temp', 'low-temp']                                              # 2009-2016

    # Retrieve heating power from the original power file
    power_heat = round(src_orig['heating'].max() / 1e3 + 5)  # Heating power in kW

    # Update config
    config['heating']['power'] = power_heat
    config['building']['year'] = year
    config['heating']['system'] = systems[years.index(year)]

    # Calculate the results for the first setup (1918)
    hts = Hts(config=config,
              weather=weather,
              power=power)
    hts.run_simulation(silent=True, log=7)
    df = hts.save_results(path=os.path.join(path, household, f'{household}_sim_{year}.csv'))

    # Check if results is already lower than the actual demand
    if ((df['heat_power'].sum() + df['cool_power'].sum())
            < (src_orig['heating'].sum() + src_orig['cooling'].sum())):
        return 1
    else:
        return 0


if __name__ == '__main__':
    if len(sys.argv) != 4:
        print("Usage: python run_v.py <county> <household> <year>")
        sys.exit(1)

    county = sys.argv[1]
    household = sys.argv[2]
    year = int(sys.argv[3])

    result = main(county, household, year)
    sys.exit(result)
