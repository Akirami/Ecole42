#!/usr/bin/python3

import math
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
    if (not isinstance(arr, np.ndarray) or not isinstance(theta, np.ndarray)
       or len(arr) == 0):
        return None
    arr = add_intercept(arr)
    print("ARR: ", arr)
    return arr.dot(theta)

def cost_elem_(y, y_hat):
    J_elem = (1 / (2 * len(y))) * (y_hat - y)**2
    return np.asarray(J_elem)


def cost_(y, y_hat):
    if len(y) != len(y_hat):
        return None
    J_value = 0.0
    J_elem = cost_elem_(y, y_hat)
    for i in J_elem:
        J_value += i
    #J_value = np.square(np.subtract(y, y_hat)).mean()
    return J_value


if __name__ == "__main__":
    x1 = np.array([[0.], [1.], [2.], [3.], [4.]])
    y1 = np.array([[2.], [7.], [12.], [17.], [22.]])
    theta1 = np.array([[2.], [4.]])
    y_hat1 = predict_(x1, theta1)

    print("YHAT: ", y_hat1)
    print("COST ELEM: \n", cost_elem_(y1, y_hat1))
    print("COST: ", cost_(y1, y_hat1))
    print("\n")

    x2 = np.array([[0.2, 2., 20.], [0.4, 4., 40.], [0.6, 6., 60.], [0.8, 8., 80.]])
    theta2 = np.array([[0.05], [1.], [1.], [1.]])
    y_hat2 = predict_(x2, theta2)
    y2 = np.array([[19.], [42.], [67.], [93.]])

    print("YHAT:", y_hat2)
    print("COST ELEM: \n", cost_elem_(y2, y_hat2))
    print("COST: ", cost_(y2, y_hat2))
    print("\n")

    x3 = np.array([[0], [15], [-9], [7], [12], [3], [-21]])
    theta3 = np.array([[0.], [1.]])
    y_hat3 = predict_(x3, theta3)
    y3 = np.array([[2], [14], [-13], [5], [12], [4], [-19]])

    print("YHAT:", y_hat3)
    print("COST ELEM: \n", cost_elem_(y3, y_hat3))
    print("COST: ", cost_(y3, y_hat3))
    print("\n")
