__author__ = "TUM-Doepfert"
__license__ = ""
__maintainer__ = "TUM-Doepfert"
__email__ = "markus.doepfert@tum.de"

import pandas as pd
import datetime as dt
import math


def format_weather_data(path: str = "./input/weather/weather.csv", snip_fcast: bool = False) -> tuple:
    """
    Formats the weather data from the lemlab format to the required SimX format

    Args:
        path: path to the weather file
        snip_fcast: delete all forecast rows from the lemlab weather file

    Returns:
        start: starting timestamp of the weather file
        end: ending timestamp of the weather file
    """

    # Read weather file
    df_weather = pd.read_csv(path)  # [:35040] # 35040 equal one year

    # Delete all forecast rows if they are still in file
    if snip_fcast:
        df_weather = df_weather[df_weather["t_now"] == df_weather["timestamp"]]

    # Get time values for weather file from first timestamp
    date = dt.datetime.utcfromtimestamp(df_weather['timestamp'][0])
    data_time = {
        "0": 0,
        "hour": date.strftime("%H"),
        "weekday": date.strftime("%w"),
        "day": date.strftime("%#d"),
        "month": date.strftime("%#m"),
        "year": date.strftime("%Y"),
    }
    df_time = pd.DataFrame([data_time])

    # Drop irrelevant columns and get first and last timestamp
    df_weather.drop(["t_now", "cloud_cover", "temp_feels_like", "temp_min", "temp_max", "pressure", "visibility",
                     "sunrise", "sunset", "pop"], axis=1, inplace=True)
    start, end = df_weather["timestamp"].iloc[0], df_weather["timestamp"].iloc[-1]

    # Change time and temperature format
    df_weather["timestamp"] = df_weather["timestamp"] - df_weather["timestamp"][0]
    df_weather["temp"] = round(df_weather["temp"] - 273.15, 2)

    # Insert column with 7 day average temperature
    df_weather.insert(2, "avg_7", 0)
    num_entries = int(3600 * 24 * 7 / (df_weather["timestamp"][1] - df_weather["timestamp"][0]))
    for week in range(math.ceil(df_weather["timestamp"].iloc[-1] / 3600 / 24 / 7)):
        df_weather.loc[week * num_entries: (week + 1) * num_entries, "avg_7"] = \
            round(df_weather["temp"].iloc[week * num_entries: (week + 1) * num_entries].mean(), 2)

    # Change order of columns to SimX format
    df_weather = df_weather[["timestamp", "temp", "avg_7", "ghi", "dhi", "wind_speed", "wind_dir", "humidity"]]

    # Save the weather data in the SimX format
    with open(f"./simx/weather.txt", "w") as file:
        file.write("#1\n")
        # Time
        file.write(f"double\tInit({df_time.shape[0]}, {df_time.shape[1]})\n")
        df_time.to_csv(file, header=False, index=False, sep='\t', line_terminator='\n')
        # Weather
        file.write("\n")
        file.write(f"double\tWeather({df_weather.shape[0]}, {df_weather.shape[1]})\n")
        df_weather.to_csv(file, header=False, index=False, sep='\t', line_terminator='\n')

    return start, end


def format_power_data(df: pd.DataFrame, start: int, end: int) -> pd.DataFrame:
    """
    Format the power profile from the lemlab format to the required GeoMA format

    Args:
        df: data frame that contains the power data
        start: start of timestamps to ensure matching times with weather file
        end: end of timestamps to ensure matching times with weather file

    Returns:
        df: edited input data frame that contains the appended columns required for the geoma calculation
    """

    # Append time relevant columns to dataframe
    df["date"] = pd.to_datetime(df["timestamp"], unit="s")
    df["time"] = df["date"].dt.strftime("%X")
    df["hours"] = df["date"].dt.strftime("%H").astype("int")

    # Limit range to length of weather file
    df = df[(df["timestamp"] >= start) & (df["timestamp"] <= end)].reset_index(drop=True)

    return df
