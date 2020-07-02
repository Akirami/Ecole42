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
	y = []
	z = theta * arr
	for i in range(len(z)):
		f = 0.0
		for j in range(len(z[i])):
			f += z[i][j]
		y.append(f)
	return y


if __name__ == "__main__":
	x = np.arange(1, 6)

	theta1 = np.array([5, 0])
	print(predict_(x, theta1))

	theta4 = np.array([-3, 1])
	print(predict_(x, theta4))