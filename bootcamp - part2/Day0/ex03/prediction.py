#!/usr/bin/python3
import numpy as np

def simple_predict(arr, theta):
    if (not isinstance(x, np.ndarray) or not isinstance(theta, np.ndarray)
        or len(x) == 0 or len(theta) != 2):
        return None
    y = theta[0] + theta[1] * arr
    return y.astype(float)


if __name__ == "__main__":
    x = np.arange(1, 6)

    theta1 = np.array([5, 0])
    print(simple_predict(x, theta1))

    theta4 = np.array([-3, 1])
    print(simple_predict(x, theta4))