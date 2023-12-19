# This file takes the results of all simulations of a building and combines them into one file.
import os
import validation.functions as f
import pandas as pd
import tqdm
import logging


def main():
    # Go through each county
    county_path = os.path.abspath('./validation/counties')
    pbar_counties = tqdm.tqdm(os.listdir(county_path), desc='Counties', position=0, leave=False)
    for county in pbar_counties:
        # Set the progressbar description
        pbar_counties.set_description(f'County: {county}')

        # Get county ID
        county_id = county.split('_')[0]

        # Load the household files
        path = f'./validation/counties/{county}/households'
        path = os.path.abspath(path)
        households = next(os.walk(path))[1]

        # Loop through households
        pbar_households = tqdm.tqdm(households, desc='Households', position=1, leave=False)
        for household in pbar_households:
            # Load the original file
            df = pd.read_csv(os.path.join(path, household, f'{household}_timeseries_adjusted.csv'),
                             index_col=0, parse_dates=True)
            # Drop the irrelevant columns and rename the relevant ones
            df = df[['heating', 'cooling']]
            df.columns = ['heating_original', 'cooling_original']

            # Get all the timeseries files of the simulations
            files = os.listdir(os.path.join(path, household))
            files = [f for f in files if f.endswith('.csv') and f.startswith(f'{household}_sim_')]

            # Loop through the files
            for file in files:
                # Load the file
                df_sim = pd.read_csv(os.path.join(path, household, file),
                                     index_col=0, parse_dates=True)

                # Change the index to datetime
                df_sim.index = pd.to_datetime(df_sim.index, unit='s')

                # Get the year
                year = int(file.split('_')[-1].split('.')[0])

                # Drop the irrelevant columns and rename the relevant ones
                df_sim = df_sim[['heat_power', 'cool_power']]
                df_sim.columns = [f'heating_{year}', f'cooling_{year}']

                # Merge the two dataframes
                df = df.merge(df_sim, how='outer', left_index=True, right_index=True)

            # Drop the rows with all NaN values
            df = df.dropna(how='all')

            # Check if the dataframe has the correct size and if not log it
            if df.size < 840960:
                logging.warning(f'{household} has less than 840960 values. ({df.shape})')

            # Save results
            df.to_csv(os.path.join(path, household, f'{household}_results.csv'))

        print('There is still an exit() here since simulation is not finished.')
        exit()


if __name__ == '__main__':
    # raise Warning('This step was already done. Move on to compare_results.py')
    main()
