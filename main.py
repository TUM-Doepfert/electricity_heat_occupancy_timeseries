__author__ = "TUM-Doepfert"
__license__ = ""
__maintainer__ = "TUM-Doepfert"
__email__ = "markus.doepfert@tum.de"

import os
import pandas as pd
from tqdm import tqdm
import input
import occup
import simx


if __name__ == '__main__':
    # ++++++++++++++++++++++++++++++++++++++++++++++ !!! IMPORTANT !!! +++++++++++++++++++++++++++++++++++++++++++++++ #
    # SimulationX has to be open before running the program due to licensing reason

    # ++++++++++++++++++++++++++++++++++++++++++++++++++ Input area ++++++++++++++++++++++++++++++++++++++++++++++++++ #

    # Power data source
    power_files = os.listdir("./input/power")  # path to power files folder

    # General parameters
    simx_id = 'ESI.SimulationX42'  # Adjust ID if other version is used (e.g. version 4.2 -> 42)
    simx_model = os.path.join(os.getcwd(), "simx", "model_woDW.isx")  # path to the SimX file

    # Building parameters
    building_name = 'simpleHeatedBuilding1'  # name of the house object in the SimX model
    building_params = {                      # keys have to correspond to SimX variable names
        "UseIndividualPresence": False,                                                     # use occupancy profiles
        # "PresenceFile": f'"{os.path.join(os.getcwd(), "simx", "occup_schedule.txt")}"',    # path of occupancy profile
        "UseIndividualElecConsumption": False,                                              # use electricity consumption
        # "ElConsumptionFile": f'"{os.path.join(os.getcwd(), "simx", "elec_consump.txt")}"', # path of electr. consumption
        "ActivateNightTimeReduction": True,                                                # use of night time reduction
        "Tnight": 16,                                                                      # night temperature in °C
        "NightTimeReductionStart": 22,                                                     # start of night time in h
        "NightTimeReductionEnd": 5,                                                        # end of night time in h
        "VariableTemperatureProfile": True,                                                # use of night time reduction
        "TMin": 18,                                                                        # night temperature in °C
    }

    # Weather parameters
    weather_name = "environment1"  # name of the object in the SimX model
    weather_params = {             # keys have to correspond to SimX variable names
        "InputFile": f'"{os.path.join(os.getcwd(), "simx", "weather.txt")}"',   # path of weather file
        "Altitude": 519,                                                        # altitude of location (e.g. Munich)
        "alpha": 11.56786,                                                      # longitude of location (e.g. Munich)
        "beta": 48.14966,                                                       # latitude of location (e.g. Munich)
    }

    # ++++++++++++++++++++++++++++++++++++++++++++++++ Simulation area +++++++++++++++++++++++++++++++++++++++++++++++ #

    # Setup progress bar
    pbar = tqdm(total=len(power_files))

    # Adjust format of weather file to suit SimX format
    start, end = input.format_weather_data()

    for file in power_files:
        # Load power file
        pbar.set_description_str(f"Profile {file}: Preparing input")
        path = os.path.join("input", "power", file)
        char = "\\"
        df = pd.read_csv(path)

        # Adjust format to required GeoMa format
        df = input.format_power_data(df, start, end)

        # GeoMA calculation
        pbar.set_description_str(f"Profile {file}: Calculating occupancy profile")
        df = occup.geoma(df)

        # Save the relevant data from df as occupancy schedule and electricity consumption for SimX to use
        pbar.set_description_str(f"Profile {file}: Calculating SimX heating demand")
        df_simx = simx.save_simx_data(df)

        # Start COM server
        simx_object = simx.start_com_server(simx_id, simx_model)

        # Change beginning and end of simulation
        simx.change_time_settings(simx_object, df_simx)

        # Change setting of the environment object
        simx.change_object_settings(simx_object, weather_name, weather_params)

        # Change settings of the building object
        object_building = simx.change_object_settings(simx_object, building_name, building_params)

        # Start simulation
        simx.start_simulation(simx_object, pbar, file)

        # Read and save results
        pbar.set_description_str(f"Profile {file}: Retrieving results and saving heating demand")
        # df = simx.save_results(df, object_building, path=os.path.join("result", path.rsplit("\\", 1)[-1]))
        df = simx.save_results(df, object_building, path=os.path.join("result", "hh_2468_0_wo_occup_wo_elec.csv"))
        exit()

        pbar.update()

    # Close progress bar
    pbar.close()
