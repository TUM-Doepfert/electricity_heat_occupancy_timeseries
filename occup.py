__author__ = "TUM-Doepfert"
__license__ = ""
__maintainer__ = "TUM-Doepfert"
__email__ = "markus.doepfert@tum.de"

import pandas as pd
from statistics import mean

# TODO: Include PHT as possible algorithms


def geoma(df: pd.DataFrame, weight: float = 0.05, threshold_evening: int = 1, start_evening: int = 21,
          end_night: int = 9, apply_night_rule: bool = True, min_vals: int = 2) -> pd.DataFrame:
    """
    Calculate the occupancy based on the power data using the GeoMA algorithm

    Args:
        df:                  data frame that contains the required information in the correct format
        weight:              lambda value that weights the impact of the current power demand on the average
        threshold_evening:   hours that occupancy needs to be detected in the evening to activate night occupancy
        start_evening:       start of evening to start counting the occupancy events required for night occupancy
        end_night:           end of the night to switch back to GeoMA detection
        apply_night_rule:    whether or not to apply the night rule or stick to continuous GeoMA detection
        min_vals:            indicates how many time steps a value must be held consecutively to be registered as change

    Returns:
        df: edited input data frame that contains the occupancy profile

    TODO: Include min_vals that makes sure that people are at least certain number of timesteps either home or not
    """

    # Auxiliary variables to be used in the for-loop
    step_size = df.at[1, "timestamp"] - df.at[0, "timestamp"]   # step size in seconds
    occ_evening = 0     # occupancy in the evening: when there is occupancy of at least n hours in the evening
                        # (defined by threshold_evening), occupancy at night is assumed
    occ_night = False   # occupancy at night: if it is set to True, it is assumed that there is occupancy until n hours
                        # (defined by end_night)

    # Check for occupancy at each time step using GeoMA algorithm
    # Calculate values for first time step outside of the loop: current power demand is moving average
    mov_avg = df.at[0, "power"]
    df.at[0, "geoma"] = mov_avg
    df.at[0, "occup"] = 1

    # Start for-loop
    for idx, val in df.iloc[1:].iterrows():

        # Update moving average based on the weight for next time step
        # Note: moving average is the weighted average of the current power demand and the previous moving average
        #       (standard ratio: 5%/95%)
        mov_avg = weight * val["power"] + (1 - weight) * mov_avg
        df.at[idx, "geoma"] = mov_avg

        # Check for occupancy using the moving average as threshold: if current value is above it, occupancy is assumed
        if val["power"] >= mov_avg:
            df.at[idx, "occup"] = 1
        else:
            df.at[idx, "occup"] = 0

        # Apply night rule if parameter set to True
        if apply_night_rule:
            # night_rule()
            # Night rule: detect occupancy in the evening and count the number of time steps occupancy is detected
            if val["hours"] >= start_evening and val["power"] >= mov_avg:
                occ_evening += step_size / 3600  # evening occupancy counter in hours

                # If evening occupancy counter exceeds threshold, set night occupancy to true
                if occ_evening >= threshold_evening:
                    occ_night = True

            # Night rule: check for occupancy during the night from midnight to morning
            if 0 <= val["hours"] < end_night:
                occ_evening = 0  # reset evening occupancy variable

                # If occupancy at night is set to True set occupancy to True regardless of power demand
                if occ_night:
                    df.at[idx, "occup"] = 1
                else:
                    df.at[idx, "occup"] = 0

            # Night rule: set night occupancy to false during the day
            if end_night <= val["hours"] < start_evening:
                occ_night = False

            # Save occupancy evening and night parameters to data frame
            df.at[idx, "occ_evening"] = occ_evening
            df.at[idx, "occ_night"] = occ_night

    return df


def pht(df: pd.DataFrame, mag_threshold: float = 0.05, detect_threshold: float = 0.3, threshold_evening: int = 1,
        start_evening: int = 21, end_night: int = 9, apply_night_rule: bool = True) -> pd.DataFrame:

    # Auxiliary variables to be used in the for-loop
    current_state, mt, increasing_mt, decreasing_mt = 0, 0, 0, 0
    step_size = df.at[1, "timestamp"] - df.at[0, "timestamp"]   # step size in seconds
    occ_evening = 0             # occupancy in the evening: when there is occupancy of at least n hours in the evening
                                # (defined by threshold_evening), occupancy at night is assumed
    occ_night = False           # occupancy at night: if it is set to True, it is assumed that there is occupancy until
                                # n hours (defined by end_night)
    avg = mean(df["power"])     # average power demand

    # Start for-loop
    for idx, val in df.iterrows():

        # Calculate all parameters
        deviation = val["power"] - avg - mag_threshold
        mt += deviation
        increasing_mt = min(increasing_mt, mt)
        decreasing_mt = max(decreasing_mt, mt)
        increasing_pht = mt - increasing_mt
        decreasing_pht = decreasing_mt - mt

        # Detect change and set the occupancy according to whether there was a change or not
        if increasing_pht > detect_threshold:       # somebody is home
            current_state = 1
            mt = 0
        elif decreasing_pht > detect_threshold:     # nobody is home
            current_state = 0
            mt = 0
        else:                                       # state is the same as previous state (no changes)
            pass

        # Assign current state to data frame
        df.at[idx, "occup"] = current_state

        # Apply night rule if parameter set to True
        if apply_night_rule:
            # Night rule: detect occupancy in the evening and count the number of time steps occupancy is detected
            if val["hours"] >= start_evening and val["power"] >= avg:
                occ_evening += step_size / 3600  # evening occupancy counter in hours

                # If evening occupancy counter exceeds threshold, set night occupancy to true
                if occ_evening >= threshold_evening:
                    occ_night = True

            # Night rule: check for occupancy during the night from midnight to morning
            if 0 <= val["hours"] < end_night:
                occ_evening = 0  # reset evening occupancy variable

                # If occupancy at night is set to True set occupancy to True regardless of power demand
                if occ_night:
                    df.at[idx, "occup"] = 1
                else:
                    df.at[idx, "occup"] = 0

            # Night rule: set night occupancy to false during the day
            if end_night <= val["hours"] < start_evening:
                occ_night = False

            # Save occupancy evening and night parameters to data frame
            df.at[idx, "occ_evening"] = occ_evening
            df.at[idx, "occ_night"] = occ_night

        # Adjust data format
        df["occup"] = df["occup"].astype("bool")

        return df


# TODO: Check if this works and implement it in the other functions
def night_rule(df: pd.DataFrame, val: pd.Series, idx: int, avg: float, occ_evening: float, threshold_evening: int = 1,
               start_evening: int = 21, end_night: int = 9, step_size: int = 900) -> tuple:

    # Night rule: detect occupancy in the evening and count the number of time steps occupancy is detected
    if val["hours"] >= start_evening and val["power"] >= avg:
        occ_evening += step_size / 3600  # evening occupancy counter in hours

        # If evening occupancy counter exceeds threshold, set night occupancy to true
        if occ_evening >= threshold_evening:
            occ_night = True

    # Night rule: check for occupancy during the night from midnight to morning
    if 0 <= val["hours"] < end_night:
        occ_evening = 0  # reset evening occupancy variable

        # If occupancy at night is set to True set occupancy to True regardless of power demand
        if occ_night:
            df.at[idx, "occup"] = 1
        else:
            df.at[idx, "occup"] = 0

    # Night rule: set night occupancy to false during the day
    if end_night <= val["hours"] < start_evening:
        occ_night = False

    # Save occupancy evening and night parameters to data frame
    df.at[idx, "occ_evening"] = occ_evening
    df.at[idx, "occ_night"] = occ_night

    return df, occ_evening
