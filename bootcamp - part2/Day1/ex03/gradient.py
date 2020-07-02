#!/usr/bin/python3

import numpy as np

def add_intercept(arr):
    if not isinstance(arr, np.ndarray):
        return None
    a = []
    if arr.ndim == 1:
        a = np.full((len(arr), 2), 1)
        for i in range(len(arr)):
            a[i][1] = arr[i]
    else:
        for i in range(len(arr)):
            a.append(np.insert(arr[i], 0, 1., axis=0))
    return np.asarray(a)

def predict_(arr, theta):
    if len(arr) < 1:
        return None
    arr = add_intercept(arr)
    return arr.dot(theta)

def simple_gradient(x, y, theta):
    if x.size == 0 or y.size == 0 or theta.size != 2:
        return None
    if x.size != y.size:
        return None
    y_hat = predict_(x, theta)

    J0 = (1 / float(len(y))) * (y_hat - y).sum()
    J1 = ((1 / float(len(y))) * (y_hat - y) * x).sum()
    return [J0, J1]


if __name__ == "__main__":
    x = np.array([12.4956442, 21.5007972, 31.5527382, 48.9145838, 57.5088733])
    y = np.array([37.4013816, 36.1473236, 45.7655287, 46.6793434, 59.5585554])

    theta1 = np.array([2, 0.7])
    print(simple_gradient(x, y, theta1))

    theta2 = np.array([1, -0.4])
    print(simple_gradient(x, y, theta2))


