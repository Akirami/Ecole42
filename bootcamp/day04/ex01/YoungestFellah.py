#!/usr/bin/python3
import pandas as pd
import numpy as np
from FileLoader import FileLoader


def youngestFellah(df, year):
    yf = df.loc[(df['Year'] == year) & (df['Sex'] == "F")].min()
    ym = df.loc[(df['Year'] == year) & (df['Sex'] == "M")].min()
    print(yf["Age"])
    yougestMaleFemale = {
        "f": yf["Age"],
        "m": ym["Age"]
    }
    return yougestMaleFemale


if __name__ == "__main__":
    loader = FileLoader()
    data = loader.load("./data/athlete_events.csv")
    # loader.display(data, 10)
    print(youngestFellah(data, 2004))