__author__ = "TUM-Doepfert"
__license__ = ""
__maintainer__ = "TUM-Doepfert"
__email__ = "markus.doepfert@tum.de"

import win32com.client
import os
import time
import pandas as pd


def save_simx_data(df: pd.DataFrame, path_elec: str = os.path.join(os.getcwd(), "simx", "elec_consump.txt"),
                   path_occup: str = os.path.join(os.getcwd(), "simx", "occup_schedule.txt")) -> pd.DataFrame:
    """
    Saves the power demand and the occupancy profile time series in the SimX format.

    :param df:          data frame that contains all necessary columns (i.e. "timestamp", "power", "occup")
    :param path_elec:   path where to save the power demand
    :param path_occup:  path where to save the occupancy profile
    :return:            returns the SimX formatted data frame
    """

    # Create SimX dataframe from input dataframe
    df_simx = pd.DataFrame()
    df_simx["timestep"] = df["timestamp"] - df.at[0, "timestamp"]
    df_simx["elec"] = df["power"]
    df_simx["occup"] = df["occup"]

    # Write independent header and save electricity consumption with the required SimX format
    with open(f"{path_elec}", "w") as file:
        file.write("#1\n")
        df_simx[['timestep', 'elec']].to_csv(file, index=False, sep='\t', line_terminator='\n',
                                             header=["double", f"Pel({df_simx[['timestep', 'elec']].shape[0]}, "
                                                               f"{df_simx[['timestep', 'elec']].shape[1]})"])

    # Write independent header and save occupancy schedule with the required SimX format
    with open(f"{path_occup}", "w") as file:
        file.write("#1\n")
        df_simx[['timestep', 'occup']].to_csv(file, index=False, sep='\t', line_terminator='\n',
                                              header=["double", f"presence({df_simx[['timestep', 'elec']].shape[0]}, "
                                                                f"{df_simx[['timestep', 'elec']].shape[1]})"])

    return df_simx


def start_com_server(simx_id: str = "ESI.SimulationX42",
                     model_path: str = os.path.join(os.getcwd(), "simx", "model.isx")) -> win32com.client.CDispatch:
    """
    Sets up and starts the COM connection

    :param simx_id:     ID of the SimX version
    :param model_path:  path of the SimX model
    :return:            SimX model object
    """

    # Setup of COM server
    sim = win32com.client.Dispatch("%s" % simx_id)                          # call SimX
    sim.Visible = True                                                      # make changes in SimX visible
    sim.Interactive = True                                                  # SimX can still be changed manually
    simx_object = sim.Documents.Open(model_path)                            # call the SimX object
    simx_object.Stop()                                                      # make sure no simulations are running
    simx_object.Reset()                                                     # reset SimX simulation

    return simx_object


def change_time_settings(simx_object: win32com.client.CDispatch, df: pd.DataFrame):
    """
    Changes the start and stop time of the simulation based on the timestamps of the dataframe

    :param simx_object:
    :param df:
    :return:
    """

    # Change the start and end time as well as the step size of the simulation
    simx_object.Parameters.Item("tStart").Unit = "s"
    simx_object.Parameters.Item("tStart").Value = 0
    simx_object.Parameters.Item("tStop").Unit = "s"
    simx_object.Parameters.Item("tStop").Value = df.iat[-1, 0] + df.iat[1, 0]
    simx_object.Parameters.Item("dtProtMin").Unit = "s"
    simx_object.Parameters.Item("dtProtMin").Value = df.iat[1, 0] - df.iat[0, 0]


def change_object_settings(simx_object: win32com.client.CDispatch, name: str, params: dict) \
        -> win32com.client.CDispatch:
    """
    Changes the parameters defined in the dictionary for the given object

    :param simx_object: SimX object
    :param name:        name of the object to be changed
    :param params:      parameters that are to be changed for the object
    :return:            object item within SimX
    """

    # Load building object
    object_item = simx_object.SimObjects.Item(name)

    # Change weather settings that are in the params dict
    for key, val in params.items():
        object_item.Parameters.Item(key).Value = val

    return object_item


def start_simulation(simx_object, pbar, file) -> None:
    """
    Runs the simulation

    :param simx_object: SimX object to be run
    :param pbar:        progress bar to update the information
    :param file:        name of the power file that is used
    :return None:
    """

    # Reset SimX
    pbar.set_description_str(f"Profile {file}: SimX simulation is being set up")
    simx_object.Reset()

    # Wait for SimX to be ready
    while simx_object.SolutionState != 2:
        time.sleep(0.1)

    # Start the simulation and wait for the response
    simx_object.Start()
    while simx_object.SolutionState == 2:
        time.sleep(0.1)

    # Wait for simInitPrepare to be done
    while simx_object.SolutionState == 4:
        time.sleep(0.1)

    # Wait while the simulation is running
    pbar.set_description_str(f"Profile {file}: SimX simulation is running")
    while simx_object.SolutionState == 8:
        time.sleep(0.1)

    pbar.set_description_str(f"Profile {file}: SimX simulation is finished")


def save_results(df: pd.DataFrame, object_building, path: str, source: str = "energy") -> pd.DataFrame:
    """
    Retrieves the thermal energy from the results, converts it to heating power and saves the results

    :param df:              data frame of the power file
    :param object_building: building object from which the thermal energy is obtained from
    :param path:            path to which the output file is saved to
    :param source:          method to use to create the heating time series; options: "energy", "power"
    :return:                data frame that contains the output
    """

    # TODO: Include option to choose if hts is to be created from power or energy time series

    # Create dataframe
    df_res = df.loc[:, ['timestamp', 'power']]

    # Retrieve specified time series and adjust format
    if source == "energy":
        df_res['th_energy'] = pd.DataFrame(object_building.Results.Item('EHeat').ProtValues) / 3600  # energy in Wh

        # Calculate the power by calculating the difference of the energy values and dividing it by the timestep
        timestep = df_res.at[1, "timestamp"] - df_res.at[0, "timestamp"]  # time step in seconds (e.g. 900 s)
        df_res["th_power"] = df_res["th_energy"].diff() / (timestep / 3600)         # power in W
        df_res.at[0, "th_power"] = df_res.at[0, "th_energy"] / (timestep / 3600)    # power in W

        # Adjust format
        df_res.drop("th_energy", axis=1, inplace=True)
        df_res["th_power"] = round(df_res["th_power"])
        if sum(df_res["th_power"].isna()) > 0:
            print("Output contains empty cells... Replaced by zeros.")
            df_res["th_power"].fillna(0)
        df_res["th_power"] = df_res["th_power"].astype("int64")
    elif source == "power":
        print("TODO")
    else:
        raise Warning(f"source value '{source}' does not exist. Please choose from the available options.")

    # Save time series
    df_res.to_csv(path, header=['timestamp', 'power', 'heat'], index=None, sep=',')

    return df_res


def save_results_paper(df: pd.DataFrame, object_building, path: str) -> pd.DataFrame:
    """
    Retrieves the thermal energy from the results, converts it to heating power and saves the results

    :param df:              data frame of the power file
    :param object_building: building object from which the thermal energy is obtained from
    :param path:            path to which the output file is saved to
    :return:                data frame that contains the output
    """

    # Create dataframe and retrieve heating energy
    df_res = df.loc[:, ['timestamp', 'power', 'geoma', 'occup', 'occ_evening', 'occ_night']]
    df_res['th_energy'] = pd.DataFrame(object_building.Results.Item('EHeat').ProtValues) / 3600  # in Wh

    # Calculate the power by calculating the difference of the energy values and dividing it by the timestep
    timestep = df_res.at[1, "timestamp"] - df_res.at[0, "timestamp"]  # time step in seconds (e.g. 900 s)
    df_res["th_power"] = df_res["th_energy"].diff() / (timestep / 3600)         # power in W
    df_res.at[0, "th_power"] = df_res.at[0, "th_energy"] / (timestep / 3600)    # power in W

    # Adjust format
    # df_res.drop("th_energy", axis=1, inplace=True)
    df_res["th_power"] = round(df_res["th_power"])
    if sum(df_res["th_power"].isna()) > 0:
        print("Output contains empty cells... Replaced by zeros.")
        df_res["th_power"].fillna(0)
    df_res["th_power"] = df_res["th_power"].astype("int64")

    # Add paper columns
    df_res['th_energy_orig'] = pd.DataFrame(object_building.Results.Item('EHeat').ProtValues)  # in J
    df_res['th_power_orig'] = pd.DataFrame(object_building.Results.Item('QHeat').ProtValues)  # in W
    df_res['el_energy_orig'] = pd.DataFrame(object_building.Results.Item('Eel').ProtValues)  # in J
    df_res['el_power_orig'] = pd.DataFrame(object_building.Results.Item('Pel').ProtValues)  # in W
    df_res['temps'] = pd.DataFrame(object_building.Results.Item('TZone').ProtValues)[1] - 273.15  # in ºC
    df_res['temp_ref_medium'] = pd.DataFrame(object_building.Results.Item('T_Ref').ProtValues) - 273.15  # in ºC
    df_res['temp_ref'] = pd.DataFrame(object_building.Results.Item('TRefSet').ProtValues) - 273.15  # in ºC

    # Save file
    df_res.to_csv(path, index=None, sep=',')

    return df_res
