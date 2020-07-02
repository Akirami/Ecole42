#!/usr/bin/python3
import numpy as np

def add_intercept(arr):
    if (not isinstance(arr, np.ndarray) or len(arr) < 1):
        return None
    a = []
    if arr.ndim == 1:
        a = np.full((len(arr), 2), 1)
        for i in range(len(arr)):
            a[i][1] = arr[i]
    else:
        for i in range(len(arr)):
            a.append(np.insert(arr[i], 0, 1., axis=0))
    a = np.asarray(a)
    return(a)

if __name__ == "__main__":
    x1 = np.arange(1, 6)
    print(add_intercept(x1))

    x2 = np.arange(1, 10).reshape((3, 3))
    print(add_intercept(x2))