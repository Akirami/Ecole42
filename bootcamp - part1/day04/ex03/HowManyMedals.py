#!/usr/bin/python3
import pandas as pd
import numpy as np
from FileLoader import FileLoader


def HowManyMedals(df, name):
    medals = df.loc[(df['Name'] == name)]
    mDict = {}
    for i in medals["Year"]:
        mDict[i] = {'G' : 0, 'S' : 0, 'B' : 0}
    for i in medals["Year"]:
        mDict[i]["G"] = medals.loc[(medals["Year"] == i)].Medal.str.count("Gold").sum()
        mDict[i]["S"] = medals.loc[(medals["Year"] == i)].Medal.str.count("Silver").sum()
        mDict[i]["B"] = medals.loc[(medals["Year"] == i)].Medal.str.count("Bronze").sum()
    return mDict


if __name__ == "__main__":
    loader = FileLoader()
    data = loader.load("./data/athlete_events.csv")

    print(HowManyMedals(data, 'Kjetil Andr Aamodt'))
