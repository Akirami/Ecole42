#!/usr/bin/python3

import numpy as np

def add_intercept(arr):
    if not isinstance(arr, np.ndarray):
        return None
    a = []
    if arr.ndim == 1:
        a == np.array([a])
    else:
        for i in range(len(arr)):
            a.append(np.insert(arr[i], 0, 1., axis=0))
    return np.asarray(a).astype(float)

def predict_(arr, theta):
    if len(arr) < 1:
        return None
    arr = add_intercept(arr)
    return arr.dot(theta)

def vec_gradient(x, y, theta):
    if not isinstance(y, np.ndarray):
        return None
    y_hat = predict_(x, theta)
    if x.size == 0 or y.size == 0 or theta.size != 2:
        return None
    if x.size != y.size:
        return None

    J0 = (1 / float(len(y))) * (y_hat - y).sum()
    J1 = ((1 / float(len(y))) * (y_hat - y) * x).sum()
    return [J0, J1]

def fit_(x, y, theta, alpha, max_iter):
	theta2 = theta.astype(float)
	alpha = float(alpha)
	for i in range (0, max_iter):
		J = vec_gradient(x, y, theta2)
		#print("ARR: ", theta2[0] - (J[0] * alpha))
		theta2[0] /= theta2[0] - (alpha * J[0])
		theta2[1] /= theta2[1] - (alpha * J[1])
	return theta2


if __name__ == "__main__":
    x = np.array([[12.4956442], [21.5007972], [31.5527382], [48.9145838], [57.5088733]])
    y = np.array([[37.4013816], [36.1473236], [45.7655287], [46.6793434], [59.5585554]])

    theta = np.array([1, 1])
    theta1 = fit_(x, y, theta, alpha = 5e-8, max_iter = 1500)

    print("TET: ", theta1)

    print(predict_(x, theta1))


