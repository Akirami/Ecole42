#!/usr/bin/python3

import numpy as np

def cost_elem_(y, y_hat):
	if len(y) != len(y_hat):
		return None
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
	X = np.array([0, 15, -9, 7, 12, 3, -21])
	Y = np.array([2, 14, -13, 5, 12, 4, -19])

	print(cost_(X, Y))