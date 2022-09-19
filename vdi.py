# Creates the VDI time series

import os
import pandas as pd
from datetime import datetime as dt


def create_vdi_profile(info: dict, paths: dict) -> pd.DataFrame:

    # Calculate annual energy demand
    info["e_el"] = info["e_el"] * 365 / info["duration"] if info["e_el"] \
        else calc_electricity(info) * 365 / info["duration"]
    info["q_th"] = info["q_th"] * 365 / info["duration"] if info["q_th"] \
        else calc_heating(info) * 365 / info["duration"]
    info["q_dw"] = info["q_dw"] * 365 / info["duration"] if info["q_dw"] \
        else calc_heating_water(info) * 365 / info["duration"]

    # Identify climate zone of the location
    info["try"] = info["try"] if info["try"] else find_try(info, paths["vdi"])

    # Calculate specific type day load profiles from the reference load profiles and type days for the given location
    type_days = calc_load_profiles(info, paths)

    # Compute the specific type days for each day depending on the weather
    df_weather = format_weather(paths["weather"])

    # Create time series from
    df_vdi = create_time_series(df_weather, type_days)

    return df_vdi


def calc_electricity(info: dict) -> int:
    demand = {
        "sfh": {        # demand per person
            "1": 2350,
            "2": 2020,
            "3": 1650,
            "4": 1500,
            "5": 1400,
            "6": 1350,
        },
        "mfh": 3000     # demand per apartment
    }

    if info["building_type"] == "sfh":
        try:
            return round(demand["sfh"][str(info["num_people"])] * info["num_people"])
        except KeyError:
            return round(demand["sfh"]["6"] * info["num_people"])
    elif info["building_type"] == "mfh":
        return round(demand["mfh"] * info["num_aps"])
    else:
        raise Warning(f"Unknown building type (info['building_type']).")


def calc_heating(info: dict) -> int:
    # TODO: Calculate from VDI 4710 or 18599
    raise Warning("Not implemented yet.")


def calc_heating_water(info: dict) -> int:
    demand = {
        "sfh": 500,     # per person
        "mfh": 1000,    # per apartment
    }

    if info["building_type"] == "sfh":
        return round(demand["sfh"] * info["num_people"])
    elif info["building_type"] == "mfh":
        return round(demand["mfh"] * info["num_aps"])
    else:
        raise Warning(f"Unknown building type (info['building_type']).")


def find_try(info: dict, path: str) -> int:
    # Get table with zip codes
    df_try = pd.read_csv(f"{path}/climate_zone.csv", dtype={"place": str, "zip_code": "Int64", "climate_zone": "Int64"})

    #  Find closest zip code to provided zip code and return the climate zone (TRY) of that zip code
    return df_try.iloc[(df_try["zip_code"] - info["zip_code"]).abs().argsort()][:1]["climate_zone"].iloc[0]


def calc_load_profiles(info: dict, paths: dict) -> dict:
    # Load reference load profiles file
    path_folder = [x[0] for x in os.walk(paths["vdi"])
                   if info["building_type"] in x[0] and info["building_age"] in x[0]
                   and "Reference load profile" in x[0]][0]
    file = [x for x in os.listdir(path_folder)
            if (str(info["resolution"] % 60) in x) or (str(int(info["resolution"] / 60)) in x)][0]
    xl = pd.ExcelFile(f"{path_folder}/{file}")

    # Add profiles to dict
    type_days = {}
    for sheet in xl.sheet_names:
        type_days[sheet] = xl.parse(sheet)
        type_days[sheet]["type_day"] = sheet

    # Sum demands if step size of the weather file differs from that of the input
    if info["step_size"] != info["resolution"]:
        num_steps = int(info["step_size"] / info["resolution"])     # number of time steps to sum
        for type_day, df in type_days.items():
            idxs = df.index[::num_steps]                            # indexes to be kept
            for idx in idxs:
                type_days[type_day].at[idx, "Electricity demand, normalized"] = \
                    sum(df["Electricity demand, normalized"].iloc[idx: idx + num_steps])
                type_days[type_day].at[idx, "Space heating demand, normalized"] = \
                    sum(df["Space heating demand, normalized"].iloc[idx: idx + num_steps])
                type_days[type_day].at[idx, "DHW demand, normalized"] = \
                    sum(df["DHW demand, normalized"].iloc[idx: idx + num_steps])

            # Drop empty rows
            type_days[type_day] = type_days[type_day].loc[idxs]

    # print(type_days["ÜWH"].to_string())

    # Load energy factors
    energy_factors = load_factors(info, paths["vdi"])

    # print(energy_factors.to_string())
    # exit()

    # Calculate the specific type day profiles based on the locations energy factors
    for type_day in type_days.keys():
        type_days[type_day]["E_el,tt"] = info["e_el"] \
                                         * (1 / 365 + info["num_people"] * energy_factors.loc["F_el_TT", type_day]) \
                                         * type_days[type_day]["Electricity demand, normalized"] \
                                         * 3600 / info["step_size"]                             # in kW
        type_days[type_day]["Q_th,tt"] = info["q_th"] * energy_factors.loc["F_Heiz_TT", type_day] \
                                         * type_days[type_day]["Space heating demand, normalized"] \
                                         * 3600 / info["step_size"]                             # in kW
        type_days[type_day]["Q_dw,tt"] = info["q_dw"] \
                                         * (1 / 365 + info["num_people"] * energy_factors.loc["F_TWE_TT", type_day]) \
                                         * type_days[type_day]["DHW demand, normalized"] \
                                         * 3600 / info["step_size"]                             # in kW

        # Only keep columns that are still required
        type_days[type_day] = type_days[type_day][["ID", "Time", "type_day", "E_el,tt", "Q_th,tt", "Q_dw,tt"]]

        # Change type to string for "Time" column as it is wrongly set
        type_days[type_day]["Time"] = type_days[type_day]["Time"].astype(str)

    return type_days


def load_factors(info: dict, path: str) -> pd.DataFrame:
    # Load energy factors file
    path_folder = [x[0] for x in os.walk(path) if info["building_type"] in x[0] and "Energy factors" in x[0]][0]
    file = [x for x in os.listdir(path_folder) if info["building_age"] in x][0]
    df = pd.read_excel(f"{path_folder}/{file}", "VDI representation", header=4, index_col=0)

    # Find according rows that match the climate zone (TRY)
    idx = df.index.get_loc(f"TRY{str(info['try']).zfill(2)}")
    df = df.iloc[idx + 2: idx + 6]
    df.index.name = None

    return df


def load_weather(path: str) -> pd.DataFrame:
    # Load weather file
    return pd.read_csv(path)


def format_weather(path: str) -> pd.DataFrame:
    # Load weather file
    df = load_weather(path)

    # Format the weather file
    df = df[df["t_now"] == df["timestamp"]]
    df.drop(columns=["t_now", "temp_feels_like", "temp_min", "temp_max", "pressure", "humidity", "visibility",
                     "wind_speed", "wind_dir", "sunrise", "sunset", "pop"],
            inplace=True)

    # Add date columns
    df["date"] = df.loc[:, "timestamp"].apply(lambda x: dt.utcfromtimestamp(x))
    df["full_date"] = df.loc[:, "date"].apply(lambda x: f"{str(x.day).zfill(2)}.{str(x.month).zfill(2)}.{str(x.year)}")
    df["vdi_date"] = df.loc[:, "date"].apply(lambda x: f"{str(x.day).zfill(2)}.{str(x.month).zfill(2)}")
    df["vdi_time"] = df.loc[:, "date"].apply(lambda x: f"{str(x.hour).zfill(2)}:{str(x.minute).zfill(2)}"
                                                       f":{str(x.second).zfill(2)}")

    # Add 7 day average values to compute season and clearness
    df["temp_avg_7"], df["cloud_eight"] = 0, 0
    num_backwards = int(3600 * 24 * 6 / (df.at[1, "timestamp"] - df.at[0, "timestamp"]))  # entries per week to go back
    for day in df["full_date"].unique():
        idx_first = df[df["full_date"] == day].index[0]     # index of the first instance of that date
        idx_last = df[df["full_date"] == day].index[-1]      # index of the last instance of that date
        # Calculate the average temperature of the last 7 days and convert to ºC
        df.loc[max(idx_first, idx_first - num_backwards): idx_last, "temp_avg_7"] = \
            round(df.loc[max(idx_first, idx_first - num_backwards): idx_last, "temp"].mean() - 273.15, 2)
        # Calculate the average clearness of the last 7 days and convert to eights
        df.loc[max(idx_first, idx_first - num_backwards): idx_last, "cloud_eight"] = \
            round(df.loc[max(idx_first, idx_first - num_backwards): idx_last, "cloud_cover"].mean() / 100 * 8, 2)

    # Determine the season of that day based on average temperature (W, Ü, S)
    df["season"] = "Ü"
    df.loc[df["temp_avg_7"] > data["weather"]["temp_summer"], "season"] = "S"
    df.loc[df["temp_avg_7"] < data["weather"]["temp_winter"], "season"] = "W"

    # Determine if workday or Sunday/holiday (W, S)
    df["day"] = "W"
    df.loc[(df["date"].dt.dayofweek == 6) | (df["vdi_date"].isin(data["holidays"].values())), "day"] = "S"

    # Determine clearness from cloud cover in eights (H, B)
    df["clearness"] = "H"
    df.loc[df["cloud_eight"] > data["weather"]["cloudy_b"], "clearness"] = "B"

    # Merge the columns to obtain the type days
    df["type_day"] = df[["season", "day", "clearness"]].agg("".join, axis=1)

    # Change SWH/SWB and SSH/SSB to SWX as SWB as they are not distinguished
    df.loc[df["type_day"].str.startswith("SW"), "type_day"] = "SWX"
    df.loc[df["type_day"].str.startswith("SS"), "type_day"] = "SSX"

    return df


def create_time_series(weather: pd.DataFrame, type_days: dict) -> pd.DataFrame:

    # Create one dataframe from type days dictionary and use type day and time as index
    df_tt = pd.concat(type_days)
    df_tt.set_index([df_tt["type_day"], df_tt["Time"]], inplace=True, drop=True)

    # Change index of weather dataframe to type day and time
    weather.set_index(["type_day", "vdi_time"], inplace=True, drop=True)

    # Add columns and fill them based on the type day and time of day
    weather["power"] = df_tt["E_el,tt"]
    weather["th_power"] = df_tt["Q_th,tt"]
    weather["dw_power"] = df_tt["Q_dw,tt"]

    weather.reset_index(inplace=True)

    return weather


def save_vdi_profile(path: str, profile: pd.DataFrame) -> None:
    profile.to_csv(path, index=False)

# ++++++++++++++++++++++++++++++++++++++++++++++++++ Input & Execution +++++++++++++++++++++++++++++++++++++++++++++++ #
data = {
    "resolution": 900,              # resolution of the VDI input; options: 900, 60, 2 in sec
    "step_size": 900,               # step size of the weather input in sec (needs to be a multiple of resolution)
    "duration": 365,  # duration of weather input in days
    "building_type": "sfh",         # options: sfh, mfh
    "building_age": "new",     # options: existing, new (only for sfh)
    "living_area": 140,             # in m²
    "num_people": 3,                # used to calculate electricity, heating and drinking water demand if not specified
    "num_aps": 1,                   # number of apartments: only relevant for mfh
    "city": "Munich",               # optional
    "zip_code": 80333,              # German zip codes only, otherwise TRY needs to be specified
    "try": 13,                      # optional
    "e_el": 2468,                   # optional: yearly electricity demand in kWh (2468 for wo/wo)
    "q_th": 9334,                   # optional: yearly heating demand in kWh (13245 for wo/wo)
    "q_dw": None,                   # optional: yearly drinking water demand in kWh (not computed)
    "weather": {                    # weather settings
        "temp_summer": 15,          # min. temperature to consider day as summer
        "temp_winter": 5,           # max. temperature to consider day as summer
        "cloudy_b": 5               # min. value to consider day as cloudy (calculated in eighths)
    },
    "holidays": {                   # holidays of the locations (leading zeros need to be added)
        "new_year": "01.01",
        "epiphany": "06.01",
        "good_friday": "02.04",
        "easter_monday": "05.04",
        "labor_day": "01.05",
        "ascension_day": "13.05",
        "whitmonday": "24.05",
        "corpus_christi": "03.06",
        "assumption_day": "15.08",
        "day_of_german_unity": "03.10",
        "all_saints_day": "01.11",
        "christmas": "25.12",
        "2nd_christmas_day": "26.12",
    },
}
paths = {
    "vdi": "./input/vdi",                                           # directory
    "weather": "./input/weather/weather_2021.csv",                  # file
    "path_output": f"./result/paper/hh_{data['e_el']}_vdi.csv",     # file
}

# Profile creation
df_vdi = create_vdi_profile(data, paths)
save_vdi_profile(paths["path_output"], df_vdi)

# -------------------------------------------------------------------------
# # Recreation of Daniel's Excel calculations
# data = {
#     "resolution": 900,              # resolution of the VDI input; options: 900, 60, 2 in sec
#     "step_size": 3600,               # step size of the weather input in sec (needs to be a multiple of resolution)
#     "duration": 365,  # duration of weather input in days
#     "building_type": "sfh",         # options: sfh, mfh
#     "building_age": "existing",     # options: existing, new (only for sfh)
#     "living_area": 110,             # in m²
#     "num_people": 3,                # used to calculate electricity, heating and drinking water demand if not specified
#     "num_aps": 1,                   # number of apartments: only relevant for mfh
#     "city": "Wetter",               # optional
#     "zip_code": 58300,              # German zip codes only, otherwise TRY needs to be specified
#     "try": 13,                    # optional
#     "e_el": 4950,                   # optional: yearly electricity demand in kWh (2468 for wo/wo)
#     "q_th": 8250,                  # optional: yearly heating demand in kWh (13245 for wo/wo)
#     "q_dw": 1500,                   # optional: yearly drinking water demand in kWh (not computed)
#     "weather": {                    # weather settings
#         "temp_summer": 15,          # min. temperature to consider day as summer
#         "temp_winter": 5,           # max. temperature to consider day as summer
#         "cloudy_b": 5               # min. value to consider day as cloudy (calculated in eighths)
#     },
#     "holidays": {
#         "new_year": "01.01",
#         "epiphany": "06.01",
#         "good_friday": "18.04",
#         "easter_monday": "21.04",
#         "labor_day": "01.05",
#         "ascension_day": "29.05",
#         "whitmonday": "09.06",
#         "assumption_day": "15.08",
#         "day_of_german_unity": "03.10",
#         "all_saints_day": "01.11",
#         "christmas": "25.12",
#         "2nd_christmas_day": "26.12",
#     }
# }
#
# df = pd.read_table("./input/weather/TRY2015_41795002403500_Jahr.dat", header=27, sep="\s+")[1:].reset_index(drop=True)
#
# # Add date columns
# df["date"] = [dt(year=2014, month=month, day=day, hour=hour) for hour, day, month in zip(df["HH"].astype("int") - 1, df["DD"].astype("int"), df["MM"].astype("int"))]
# df["vdi_date"] = [f"{str(int(day)).zfill(2)}.{str(int(month)).zfill(2)}" for day, month in zip(df["DD"], df["MM"])]
# df["vdi_time"] = [f"{str(int(hour)).zfill(2)}:00:00" for hour in df["HH"] - 1]
#
# # Add 7 day average values to compute season and clearness
# df["temp_avg"], df["temp_avg_7"], df["cloud_eight"], df["cloud_eight_7"] = 0, 0, 0, 0
# num_backwards = 24 * 6  # entries per week to go back
# for day in df["vdi_date"].unique():
#     idx_first = df[df["vdi_date"] == day].index[0]  # index of the first instance of that date
#     idx_last = df[df["vdi_date"] == day].index[-1]  # index of the last instance of that date
#     # Calculate the average temperature of the last 7 days and convert to ºC
#     df.loc[max(idx_first, idx_first - num_backwards): idx_last, "temp_avg"] = \
#         round(df.loc[max(idx_first, idx_first - num_backwards): idx_last, "t"].mean(), 2)
#     df.loc[max(idx_first, idx_first - num_backwards): idx_last, "temp_avg_7"] = \
#         round(df.loc[max(min(idx_first, idx_first - num_backwards), 0): idx_last, "t"].mean(), 2)
#     # Calculate the average clearness of the last 7 days and convert to eights
#     df.loc[max(idx_first, idx_first - num_backwards): idx_last, "cloud_eight"] = \
#         round(df.loc[max(idx_first, idx_first - num_backwards): idx_last, "N"].mean(), 2)
#     df.loc[max(idx_first, idx_first - num_backwards): idx_last, "cloud_eight_7"] = \
#         round(df.loc[max(min(idx_first, idx_first - num_backwards), 0): idx_last, "N"].mean(), 2)
#
# # Determine the season of that day based on average temperature (W, Ü, S)
# df["season"] = "Ü"
# df.loc[df["temp_avg_7"] > data["weather"]["temp_summer"], "season"] = "S"
# df.loc[df["temp_avg_7"] < data["weather"]["temp_winter"], "season"] = "W"
#
# # Determine if workday or Sunday/holiday (W, S)
# df["day"] = "W"
# df.loc[(df["date"].dt.dayofweek == 6) | (df["vdi_date"].isin(data["holidays"].values())), "day"] = "S"
#
# # Determine clearness from cloud cover in eights (H, B)
# df["clearness"] = "H"
# df.loc[df["cloud_eight"] > data["weather"]["cloudy_b"], "clearness"] = "B"
#
# # Merge the columns to obtain the type days
# df["type_day"] = df[["season", "day", "clearness"]].agg("".join, axis=1)
#
# # Change SWH/SWB and SSH/SSB to SWX as SWB as they are not distinguished
# df.loc[df["type_day"].str.startswith("SW"), "type_day"] = "SWX"
# df.loc[df["type_day"].str.startswith("SS"), "type_day"] = "SSX"
#
# # df.to_csv("./input/weather/TRY2015_41795002403500_Jahr.csv", index=False)
# # print(df[:200:24].to_string())
#
# # Calculate annual energy demand
# data["e_el"] = data["e_el"]
# data["q_th"] = data["q_th"]
# data["q_dw"] = data["q_dw"]
#
# # Identify climate zone of the location
# data["try"] = data["try"]
#
# # Calculate specific type day load profiles from the reference load profiles and type days for the given location
# type_days = calc_load_profiles(data, paths)
# # print(type_days["ÜWH"].to_string())
# # # Compute the specific type days for each day depending on the weather
# # df_weather = format_weather(paths["weather"])
#
# # Create time series from
# df_vdi = create_time_series(df, type_days)
# print(df_vdi[:30].to_string())
# types = ["ÜWH", "ÜWB", "ÜSH", "ÜSB", "SWX", "SSX", "WWH", "WWB", "WSH", "WSB"]
# for t in types:
#     print(f"{t}: {round(len(df[df['type_day'].str.startswith(t)]) / 24)}")
# print(round(sum(df_vdi["power"]), 1), round(sum(df_vdi["th_power"]), 1), round(sum(df_vdi["dw_power"]), 1))
