import pandas as pd

demand = 2468

# With occupancy and with electricity consumption
df_w_w = pd.read_csv(f"result/hh_{demand}_0.csv")

# Without occupancy and with electricity consumption
df_wo_w = pd.read_csv(f"result/hh_{demand}_0_wo_occup.csv")

# Without occupancy and without electricity consumption
df_wo_wo = pd.read_csv(f"result/hh_{demand}_0_wo_occup_wo_elec.csv")

print("Total heating energy demand")
print(f"With occupancy and with electricity consumption (w/w): {round(sum(df_w_w['heat']) / 4 / 1e3)} kWh")
print(f"Without occupancy and with electricity consumption (wo/w): {round(sum(df_wo_w['heat']) / 4 / 1e3)} kWh")
print(f"Without occupancy and without electricity consumption (wo/wo): {round(sum(df_wo_wo['heat']) / 4 / 1e3)} kWh")
# print(f"Difference (w-wo): {sum(df_w['heat']) / 4 - sum(df_wo['heat']) / 4}")

print("Observations:\n"
      "1. With occupancy the demand is higher, which is unplausible. The wo/wo scenario is much higher due to a bug\n"
      "2. With occupancy the temperature varies much more often and goes way too often under the comfort level "
      "-> People are not that long gone and does not add up with the increased demand (observable in SimX)\n"
      "3. In the without occupancy scenario (same with others) the temperature decreases on very cold days (<-10 ºC) "
      "but the heat demand is still zero for 12 hours of the day. -> Cannot be the night time reduction as it is from "
      "22 to 5 o'clock\n"
      "4. The heat demand shows a very high heat demand every morning for around an hour and then goes lower -> also "
      "does not add up to the colder indoor temperature as apparently the heating system can heat more")
