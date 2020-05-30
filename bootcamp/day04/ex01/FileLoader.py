#!/usr/bin/python3
import pandas as pd
import numpy as np


class FileLoader:
    def load(self, path):
        df = pd.read_csv(path)
        print("Loading dataset of dimensions %d %d" % (df.shape[0], df.shape[1]))
        return df

    def display(self, df, n):
        df_len = len(df.index)
        if n > 0:
            print(df.head(10))
        elif n < 0:
            print(df.tail(10))
