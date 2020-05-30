#!/usr/bin/python3
import pandas as pd
import numpy as np


class FileLoader:
    def load(self, path):
        return pd.read_csv(path) 

    def display(self, df, n):
        df_len = len(df.index)
        if n > 0:
            print(df.head(10))
        elif n < 0:
            print(df.tail(10))


if __name__ == "__main__":
    f = FileLoader()
    data = f.load("./athlete_events.csv")

    f.display(data, 10)
    f.display(data, -10)