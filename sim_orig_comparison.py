"""Creates a plot that compares the simulated and original heating demand over time."""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Generate datetime index for one year in 1-hour intervals
start_date = pd.to_datetime('2023-01-01')
end_date = start_date + pd.DateOffset(days=365)
datetime_index = pd.date_range(start=start_date, end=end_date, freq='1H')
datetime_index = datetime_index[:-1]


# Create simulated and original data for 30 time series
n_timeseries = 30
n_rows = len(datetime_index)

simulated_data = np.random.normal(loc=1000, scale=3000, size=(n_rows, n_timeseries))
original_data = np.random.normal(loc=1000, scale=3000, size=(n_rows, n_timeseries))

# Create DataFrame
simulated_df = pd.DataFrame(simulated_data, index=datetime_index)
original_df = pd.DataFrame(original_data, index=datetime_index)

# Set all values below 0 to 0
simulated_df[simulated_df < 0] = 0
original_df[original_df < 0] = 0

# Concatenate the DataFrames and create multi-level columns
data = pd.concat([original_df, simulated_df], axis=1)
data.columns = pd.MultiIndex.from_product([range(n_timeseries), ['Original', 'Simulated']])

# Make each row the sum of the previous rows
data = data.cumsum(axis=0)

# Round and convert to int (makes it easier to see the differences)
data = round(data).astype(int)

# Add a ratio column for each column and group them under the correct first level column
for column in data.columns.levels[0]:
    data[(column, 'Ratio')] = data[(column, 'Simulated')] / data[(column, 'Original')]

# Get the maximum value of each 'Original' column
max_values = data.xs('Original', level=1, axis=1).max(axis=0)

print(data.iloc[:5, :].to_string())
print(data.iloc[-5:, :].to_string())

# Divide both 'Original' and 'Simulated' columns by the corresponding maximum values
for column in data.columns.levels[0]:
    data[(column, 'Simulated')] /= max_values[column]
    data[(column, 'Original')] /= max_values[column]

print(data.iloc[:5, :].to_string())
print(data.iloc[-5:, :].to_string())

# data.columns = pd.MultiIndex.from_product([data.columns.levels[0], ['Original', 'Simulated', 'Ratio']])


# Use the ratio columns to calculate the median, upper quartile, lower quartile, upper 95%, and lower 5%
# Calculate the statistics for each row using the ratio columns
data[('Stats', 'Lower 5%')] = data.xs('Ratio', level=1, axis=1).quantile(0.05, axis=1)
data[('Stats', 'Lower Quartile')] = data.xs('Ratio', level=1, axis=1).quantile(0.25, axis=1)
data[('Stats', 'Median')] = data.xs('Ratio', level=1, axis=1).median(axis=1)
data[('Stats', 'Upper Quartile')] = data.xs('Ratio', level=1, axis=1).quantile(0.75, axis=1)
data[('Stats', 'Upper 95%')] = data.xs('Ratio', level=1, axis=1).quantile(0.95, axis=1)

# Calculate the statistics for each row based on the 'Original' and 'Simulated' columns
data[('Stats', 'Lower 5% (Original)')] = data.xs('Original', level=1, axis=1).quantile(0.05, axis=1)
data[('Stats', 'Lower Quartile (Original)')] = data.xs('Original', level=1, axis=1).quantile(0.25, axis=1)
data[('Stats', 'Median (Original)')] = data.xs('Original', level=1, axis=1).median(axis=1)
data[('Stats', 'Upper Quartile (Original)')] = data.xs('Original', level=1, axis=1).quantile(0.75, axis=1)
data[('Stats', 'Upper 95% (Original)')] = data.xs('Original', level=1, axis=1).quantile(0.95, axis=1)

data[('Stats', 'Lower 5% (Simulated)')] = data.xs('Simulated', level=1, axis=1).quantile(0.05, axis=1)
data[('Stats', 'Lower Quartile (Simulated)')] = data.xs('Simulated', level=1, axis=1).quantile(0.25, axis=1)
data[('Stats', 'Median (Simulated)')] = data.xs('Simulated', level=1, axis=1).median(axis=1)
data[('Stats', 'Upper Quartile (Simulated)')] = data.xs('Simulated', level=1, axis=1).quantile(0.75, axis=1)
data[('Stats', 'Upper 95% (Simulated)')] = data.xs('Simulated', level=1, axis=1).quantile(0.95, axis=1)

# Fill NaN values with 0
data = data.fillna(0)

print(data.iloc[:5, :].to_string())
print(data.iloc[-5:, :].to_string())

# Create the figure and axis
plt.figure(figsize=(10, 10))
ax = plt.gca()

# Define a colormap with different shades of orange
n_shades = 4
cmap = plt.get_cmap('Oranges', n_shades)

# Plot the custom boxplot-like representation
stats = ['Lower 5%', 'Lower Quartile', 'Median', 'Upper Quartile', 'Upper 95%']
for i, stat in enumerate(stats):
    color = cmap(i / (n_shades - 1))  # Get the color from the colormap
    plt.plot(data[('Stats', f'{stat} (Original)')], data[('Stats', f'{stat} (Simulated)')], color='black', linewidth=1, label=stat)
    if i < n_shades:
        if 1 < i < 3:
            alpha = 1
        else:
            alpha = 0.5
        plt.fill_between(data[('Stats', f'{stat} (Original)')], data[('Stats', f'{stats[i]} (Simulated)')], data[('Stats', f'{stats[i + 1]} (Simulated)')], color='Orange', alpha=alpha)

# Plot the line from (0,0) to (1,1) for the ratio
plt.plot([0, 1], [0, 1], color='black', linestyle='dashed', label='Ratio of 1', linewidth=2)

# Set axis labels and title
plt.xlabel('Normalized Heating Demand (Original)')
plt.ylabel('Ratio (Simulated / Original)')
plt.title('Comparison of Simulated and Original Heating Ratios over Time')

# Set x-axis and y-axis limits
plt.xlim(0, 1.1)
plt.ylim(0, 1.1)

# Add a legend
plt.legend()

# Show the grid
plt.grid(True)

# Display the plot
plt.tight_layout()
plt.show()
