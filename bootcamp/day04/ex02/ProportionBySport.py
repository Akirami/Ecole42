#!/usr/bin/python3
import pandas as pd
import numpy as np
from FileLoader import FileLoader


def proportionBySport(df, year, sport, genre):
    #df = df.drop_duplicates(subset='Name', keep='last')
    fSports = df.loc[(df['Year'] == year) & (df['Sex'] ==\
        genre)].drop_duplicates(subset='Name', keep='last').shape[0]
    fTennis = df.loc[(df['Year'] == year) & (df['Sport'] == sport) &\
    (df['Sex'] == genre)].drop_duplicates(subset='Name', keep='last').shape[0]
    return fTennis / fSports


if __name__ == "__main__":
    loader = FileLoader()
    data = loader.load("./data/athlete_events.csv")
    # loader.display(data, 10)
    print(proportionBySport(data, 2004,'Tennis', 'F'))
