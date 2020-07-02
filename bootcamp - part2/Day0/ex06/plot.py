#!/usr/bin/python3
import numpy as np
import matplotlib.pyplot as plt

def plot(x, y, theta):
	plt.scatter(x, y, s = 20)

	plt.title('Matplotlib')
	plt.xlabel('x')
	plt.ylabel('y')
	y_pred = theta[0] + theta[1] * x 
	plt.plot(x, y_pred, color = "green")
	plt.show()

if __name__ == "__main__":
	x = np.arange(1, 6)
	y = np.array([3.74013816, 3.61473236, 4.57655287, 4.66793434, 5.95585554])
	theta1 = np.array([4.5, -0.2])
	plot(x, y, theta1)

	theta2 = np.array([-1.5, 2])
	plot(x, y, theta2)