from hts import Hts
from pprint import pprint

method = None #run.py 'fischer'
year = 2022
energy = 4703

match method:
    case 'peacock':
        hts = Hts(path_weather="./input/weather_2013.csv", path_power="./input/power_2013.csv")
        hts.run_simulation()
        hts.save_results(path='./figures/validation/peacock/results_2013.csv')
    case 'fischer':
        hts = Hts(path_config=f'./figures/validation/fischer/input_{year}.yml',
                  path_weather="./input/weather_2010_2021_4.csv",
                  path_power=f"./input/power/hh_{energy}_0.csv")
        hts.run_simulation()
        hts.save_results(path=f'./figures/validation/fischer/results_{year}.csv')
    case other:
        hts = Hts()
        hts.run_simulation()
        hts.save_results()

