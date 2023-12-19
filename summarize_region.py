# This file picks the best fitting simulated results for each building and saves them in a new file with the original
# results.
import os
import validation.functions as f
import pandas as pd
import tqdm
import logging
from pprint import pprint
import numpy as np


def main(features):
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

        # Create list to store the results
        results_list = []

        # Loop through households
        pbar_households = tqdm.tqdm(households, desc='Households', position=1, leave=False)
        for household in pbar_households:
            # Load the results file
            df_res = pd.read_csv(os.path.join(path, household, f'{household}_results.csv'),
                                 index_col=0, parse_dates=True)

            # Find the column categories
            col_ends = set([col.split('_')[-1] for col in df_res.columns])

            # Compute the sum of the features for each column category
            res = {}
            for col_end in col_ends:
                # Get the columns with this column category
                cols = [col for col in df_res.columns if col.endswith(col_end)]

                # Get the sum of the features (and convert to MWh)
                res[col_end] = round(df_res[cols].sum(axis=1).sum(axis=0) * 0.25 / 1e6, 2)

            # Get the year which is closest to the original value
            best = np.inf
            best_year = 1918
            for key, val in res.items():
                if key == 'original':
                    continue

                # Calculate the difference to the original value
                res[key] = round(abs(res['original'] - val) / res['original'], 3)

                # Check if this value is better than the previous best
                if res[key] < best:
                    best = res[key]
                    best_year = key


            # Get the original and best fitting simulation columns
            cols = [col for col in df_res.columns if col.endswith(str(best_year)) or col.endswith('original')]
            df_res = df_res[cols]

            # Rename the columns
            df_res.columns = [f'{col.split("_")[0]}_sim' if col.endswith(str(best_year)) else col for col in df_res.columns ]
            df_res.columns = [f'{household}_{col}' for col in df_res.columns]

            # Add the results to the list
            results_list.append(df_res)
            print(len(results_list))
            print(household)

            if household == '120812':
                break

        # Combine all dataframes
        df = pd.concat(results_list, axis=1)

        print(df.head().to_string())

        exit()

        # TODO: You can also do something that you search for the closest value that is still above and then run the insulation script. It should be very similar to run_v.ps1

            # print(col_ends)
            # exit()


if __name__ == '__main__':
    # raise Warning('This step was already done. Move on to sim_orig_comparison.py')

    features_to_check_for = ['heating', 'cooling']
    main(features_to_check_for)
