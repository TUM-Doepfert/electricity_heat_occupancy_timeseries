# Mainly plots for the paper

import os
import math
import pandas as pd
from datetime import datetime as dt
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.dates as mdates

# Style settings
pd.options.mode.chained_assignment = None
# matplotlib.use("pgf")
# matplotlib.rcParams.update({
#     "pgf.texsystem": "pdflatex",
#     'font.family': 'serif',
#     'text.usetex': True,
#     'pgf.rcfonts': False,
# })
plt.style.use('seaborn')


def plot_geoma(data: dict, time: list = None):

    # General settings
    start_evening = 21
    end_night = 9

    # Prepare input data
    df = data["occup_True_elec_True"]
    df = df[(df["timestamp"] >= time[0]) & (df["timestamp"] <= time[1])]
    df["power"] /= 1e3  # W to kW
    df["geoma"] /= 1e3  # W to kW
    df["date"] = df.loc[:, "timestamp"].apply(lambda x: dt.utcfromtimestamp(x))

    # Occupancy by GeoMA
    df["occupancy"] = (df["power"] - df["geoma"]) > 0
    df["occupancy"] = df["power"] * df["occupancy"]
    df["occupancy"].replace(0, np.nan, inplace=True)

    # evening and night fill
    df["evening"] = df["date"].apply(lambda x: x.hour)
    df["night"] = df["evening"][:]
    df["evening"] = df["evening"].loc[df["evening"] >= start_evening]
    df["evening"].loc[~df["evening"].isnull()] = max(df["power"]) * 1.1
    df["evening"] = df["evening"].interpolate(method="pad", limit=1)
    # df["evening_occup"] = 0
    # df["evening_unoccup"] = 0
    df["night"] = df["night"].loc[df["night"] < end_night]
    df["night"].loc[~df["night"].isnull()] = max(df["power"]) * 1.1
    df["night"] = df["night"].interpolate(method="pad", limit=1)
    # df["night_occup"] = 0
    # df["night_unoccup"] = 0

    # Occupancy incl. night rule
    df["occupancy_night"] = df["power"] * df["occup"]
    df["occupancy_night"] = df["occupancy_night"].loc[df["night"] > 0]

    # Plotting
    fig, ax = plt.subplots()

    # fill area of evening hours and plot text
    evening = ax.fill_between(df["date"], df["evening"], color="darkgray", alpha=.5, linewidth=0)
    for num in range(len(evening.get_paths())):
        (x0, y0), (x1, y1) = evening.get_paths()[num].get_extents().get_points()
        ax.text((x0 + x1) / 2, max(y0, y1) * 0.95, "eve", ha="center", va="center", fontsize=10)

    # fill area of night hours and plot text
    night = ax.fill_between(df["date"], df["night"], color="dimgray",  alpha=.5, linewidth=0)
    for num in range(len(night.get_paths()) - 1):  # - 1 because midnight is still included
        (x0, y0), (x1, y1) = night.get_paths()[num].get_extents().get_points()
        ax.text((x0 + x1) / 2, max(y0, y1) * 0.95, "night", ha="center", va="center", fontsize=10)

    ax.plot(df["date"], df["power"], "-", linewidth=1.5, color="dimgrey", alpha=1, label="power consumption")
    ax.plot(df["date"], df["geoma"], "--", linewidth=1.5, color="darkorange", alpha=0.7, label="moving average")
    ax.fill_between(df["date"], df["occupancy"], color="limegreen", alpha=.7, linewidth=0, label="occupied")
    ax.fill_between(df["date"], df["occupancy_night"], color="darkgreen", alpha=.4, linewidth=0, label="incl. night rule")

    ax.set_xlim(df["date"].iloc[0], df["date"].iloc[-1])
    ax.set_ylim(0, max(df["power"]) * 1.1)
    plt.ylabel("Power in kW")
    for tick in (ax.get_xticklabels() + ax.get_yticklabels()):
        tick.set_fontsize(11)
    ax.xaxis.set_major_locator(mdates.DayLocator())
    ax.xaxis.set_major_formatter(mdates.DateFormatter("%d.%m"))
    #ax.xaxis.set_minor_locator(mdates.HourLocator())
    #ax.xaxis.set_minor_formatter(mdates.DateFormatter("%H h"))
    ax.minorticks_on()
    plt.legend(loc="upper left", frameon=True, framealpha=0.8, facecolor="white", edgecolor="dimgrey",
               fontsize=10, borderaxespad=1.5, labelspacing=0.3)
    fig.set_size_inches(w=6, h=2.5)
    plt.tight_layout()
    plt.show()
    # plt.savefig("geoma.png")
    # plt.savefig("geoma.pgf")


def plot_vdi(data: dict, time: list = None):

    # Prepare input data
    df_vdi = data["vdi"]
    df_simx = data["occup_False_elec_False"]
    df_vdi = df_vdi[(df_vdi["timestamp"] >= time[0]) & (df_vdi["timestamp"] <= time[1])]
    df_simx = df_simx[(df_simx["timestamp"] >= time[0]) & (df_simx["timestamp"] <= time[1])]
    df_vdi["temp"] -= 273.15    # K to °C
    df_simx["th_power"] /= 1e3  # W to kW
    df_vdi["date"] = df_vdi.loc[:, "timestamp"].apply(lambda x: dt.utcfromtimestamp(x))
    df_simx["date"] = df_simx.loc[:, "timestamp"].apply(lambda x: dt.utcfromtimestamp(x))

    # Plotting
    fig, ax1 = plt.subplots()
    ax2 = ax1.twinx()

    # Power
    p_simx, = ax1.plot(df_simx["date"], df_simx["th_power"], "-", linewidth=1.5, color="dimgrey", alpha=1, label="SimX")
    p_vdi, = ax1.plot(df_vdi["date"], df_vdi["th_power"], "--", linewidth=1.5, color="dimgrey", alpha=0.8, label="VDI")

    # Temperature
    t_simx, = ax2.plot(df_vdi["date"], df_vdi["temp"], "-", linewidth=1.5, color="indianred", alpha=1, label="SimX")
    t_vdi, = ax2.plot(df_vdi["date"], df_vdi["temp_avg_7"], "--", linewidth=1.5, color="indianred", alpha=0.8, label="VDI")
    # t_in, = ax2.plot(df_simx["date"], df_simx["temps"], "-.", linewidth=1.5, color="indianred", alpha=0.5, label="indoor")
    # t_ref, = ax2.plot(df_simx["date"], [21] * len(df_simx["date"]), ":", linewidth=1.5, color="indianred", alpha=0.3, label="reference")

    # Type days
    for _, day in df_vdi.loc[df_vdi["vdi_time"] == "12:00:00"].iterrows():
        ax1.text(day["date"], -0.25, day["type_day"], verticalalignment="center", horizontalalignment="center", fontsize=10)

    # Params: axes & labels
    ax1.set_xlim(df_vdi["date"].iloc[0], df_vdi["date"].iloc[-1])
    ax1.set_ylim(-0.5, math.ceil(max(max(df_vdi["th_power"]), max(df_simx["th_power"])) * 1.1))
    ax1.set_ylabel("Power in kW", fontsize=13)
    ax2.set_ylabel("Temperature in °C", fontsize=13)
    for tick in (ax1.get_xticklabels() + ax1.get_yticklabels() + ax2.get_yticklabels()):
        tick.set_fontsize(11)
    ax1.xaxis.set_major_locator(mdates.DayLocator())
    ax1.xaxis.set_major_formatter(mdates.DateFormatter("%d.%m"))

    # Params: legend
    ax1.legend(title="Power", loc=2, frameon=True, framealpha=0.8, facecolor="white", edgecolor="dimgrey",
               fontsize=10, title_fontproperties={'weight': 'bold', 'size': 10})
    ax2.legend(title="Temperature", loc=1, frameon=True, framealpha=0.8, facecolor="white", edgecolor="indianred",
               fontsize=10, title_fontproperties={'weight': 'bold', 'size': 10})

    # Params: Tidy up
    fig.set_size_inches(w=6, h=3)
    ax2.grid(False)
    plt.tight_layout()
    plt.show()
    # plt.savefig("vdi.png")
    # plt.savefig("vdi.pgf")


def plot_profiles(data: dict, time: list = None):

    # General setup of plot
    fig, axs = plt.subplots(2, 2, sharex=True, sharey=True)

    # Loop through dictionary entries to find relevant dataframes
    max_th_power = 0
    for key in data.keys():
        if "occup_False" in key and "elec_False" in key:
            # Data
            df = data[key]
            df = df[(df["timestamp"] >= time[0]) & (df["timestamp"] <= time[1])]
            df["date"] = df.loc[:, "timestamp"].apply(lambda x: dt.utcfromtimestamp(x))
            df["th_power"] /= 1e3  # W to kW

            # Plotting
            ax1 = axs[0, 0].twinx()
            # Thermal power
            axs[0, 0].plot(df["date"], df["th_power"], linewidth=1.5, alpha=1, color="dimgray", label="power")
            y_ref, = axs[1, 0].plot(df["date"], df["th_power"], "--", linewidth=1, alpha=0.8, color="dimgray", label="ref. power")
            axs[0, 1].plot(df["date"], df["th_power"], "--", linewidth=1, alpha=0.8, color="dimgray")
            axs[1, 1].plot(df["date"], df["th_power"], "--", linewidth=1, alpha=0.8, color="dimgray")
            # Indoor temperature
            ax1.plot(df["date"], df["temps"], linewidth=1, alpha=1, color="indianred", label="indoor temp.")
            ax1.set_ylim(16, 23)
            ax1.set_yticks(list(range(16, 23, 2)))

            # Params
            axs[0, 0].set_ylabel("Power in kW", fontsize=10)
            # axs[0, 0].set_yticks(range(math.ceil(max_th_power), 2))
            ax1.grid(False)
            ax1.get_yaxis().set_visible(False)
            axs[0, 0].set_title("without occupancy / without electricity", size=10)

        elif "occup_False" in key and "elec_True" in key:
            # Data
            df = data[key]
            df = df[(df["timestamp"] >= time[0]) & (df["timestamp"] <= time[1])]
            df["date"] = df.loc[:, "timestamp"].apply(lambda x: dt.utcfromtimestamp(x))
            df["th_power"] /= 1e3  # W to kW
            # Plotting
            ax1 = axs[1, 0].twinx()
            # Thermal power
            axs[1, 0].plot(df["date"], df["th_power"], linewidth=1.5, alpha=1, color="dimgray")
            # Indoor temperature
            ax1.plot(df["date"], df["temps"], linewidth=1, alpha=1, color="indianred")
            ax1.set_ylim(16, 23)
            ax1.set_yticks(list(range(16, 23, 2)))

            # Params
            axs[1, 0].set_ylabel("Power in kW", fontsize=10)
            # axs[1, 0].set_yticks(range(math.ceil(max_th_power), 2))
            ax1.grid(False)
            ax1.get_yaxis().set_visible(False)
            axs[1, 0].set_title("without occupancy / with electricity", size=10)

        elif "occup_True" in key and "elec_False" in key:
            # Data
            df = data[key]
            df = df[(df["timestamp"] >= time[0]) & (df["timestamp"] <= time[1])]
            df["date"] = df.loc[:, "timestamp"].apply(lambda x: dt.utcfromtimestamp(x))
            df["th_power"] /= 1e3  # W to kW

            # Plotting
            ax1 = axs[0, 1].twinx()
            # Thermal power
            axs[0, 1].plot(df["date"], df["th_power"], linewidth=1.5, alpha=1, color="dimgray")
            # Indoor temperature
            ax1.plot(df["date"], df["temps"], linewidth=1, alpha=1, color="indianred")
            ax1.set_ylim(16, 23)
            ax1.set_yticks(list(range(16, 23, 2)))

            # Params
            ax1.set_ylabel("Temperature in °C", fontsize=10)
            ax1.grid(False)
            axs[0, 1].set_title("with occupancy / without electricity", size=10)

        elif "occup_True" in key and "elec_True" in key:
            # Data
            df = data[key]
            df = df[(df["timestamp"] >= time[0]) & (df["timestamp"] <= time[1])]
            df["date"] = df.loc[:, "timestamp"].apply(lambda x: dt.utcfromtimestamp(x))
            df["th_power"] /= 1e3  # W to kW

            # Plotting
            ax1 = axs[1, 1].twinx()
            # Thermal power
            axs[1, 1].plot(df["date"], df["th_power"], linewidth=1.5, alpha=1, color="dimgray")
            # Indoor temperature
            ax1.plot(df["date"], df["temps"], linewidth=1, alpha=1, color="indianred")
            ax1.set_ylim(16, 23)
            ax1.set_yticks(list(range(16, 23, 2)))

            # Params
            ax1.set_ylabel("Temperature in °C", fontsize=10)
            ax1.grid(False)
            axs[1, 1].set_title("with occupancy / with electricity", size=10)

        else:
            continue

        try:
            max_th_power = max(max_th_power, max(df["th_power"]))
        except KeyError:
            pass

    # General settings for each subplot
    for idx, ax in enumerate(axs):
        for idxx, a in enumerate(ax):
            # Occupancy
            df["occupancy"] = math.ceil(max_th_power * 1.1) * df["occup"]
            df["occupancy"].replace(0, np.nan, inplace=True)
            if idx == 1 and idxx == 1:
                a.fill_between(df["date"], df["occupancy"], color="darkgreen", alpha=.4, linewidth=0, label="occupied")
            else:
                a.fill_between(df["date"], df["occupancy"], color="darkgreen", alpha=.4, linewidth=0)

            a.set_xlim(df["date"].iloc[0], df["date"].iloc[-2])
            a.set_yticks(list(range(0, math.ceil(max_th_power), 2)))
            a.set_ylim(0, math.ceil(max_th_power * 1.1))
            a.xaxis.set_major_locator(mdates.DayLocator())
            a.xaxis.set_major_formatter(mdates.DateFormatter("%d.%m"))
            a.minorticks_on()

    lines_labels = [ax.get_legend_handles_labels() for ax in fig.axes]
    lines, labels = [sum(lol, []) for lol in zip(*lines_labels)]
    fig.legend(lines, labels, loc=8, frameon=True, framealpha=0.8, facecolor="white", edgecolor="dimgrey",
               fontsize=10, ncol=len(labels))

    fig.set_size_inches(w=6, h=3)
    plt.tight_layout()
    plt.subplots_adjust(bottom=0.2)
    plt.show()
    # plt.savefig("profiles.png")
    # plt.savefig("profiles.pgf")


def create_plots(data: dict, time: list = None):
    plot_geoma(data, time)
    plot_vdi(data, time)
    plot_profiles(data, time)


# get input data
time_span = [1609459200 + 86400 * 49, 1609459200 + 86400 * 52]
power = 2468
input_data = dict()
path = "./result/paper"
for file in os.listdir(path):
    if str(power) in file:
        input_data[f"{file.split('_', 3)[-1].split('.', 1)[0]}"] = pd.read_csv(os.path.join(path, file))

plot_geoma(input_data, time_span)
plot_vdi(input_data, time_span)
plot_profiles(input_data, time_span)
