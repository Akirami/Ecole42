#!/usr/bin/python3

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from sklearn.metrics import mean_squared_error
import matplotlib.pyplot as plt

class MyLinearRegression():
    """Description:My personnal 
    linear regression class 
    to fit like a boss."""
    def __init__(self, x, y, thetas, alpha=0.001, n_cycle=1000):
        self.x = x
        self.y = y
        self.y_hat = 0
        self.alpha = alpha
        self.max_iter = n_cycle
        self.thetas = np.asarray(thetas)

    def add_intercept(self, arr):
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
        return np.asarray(a).astype(float)

    def predict_(self, x):
        if not isinstance(x, np.ndarray) or len(x) == 0:
            return None
        x2 = self.add_intercept(x)
        self.plot(x, x2.dot(self.thetas), self.thetas)
        self.y_hat = x2.dot(self.thetas)
        return self.y_hat

    def cost_elem_(self, x, y):
        x = np.reshape(x, (len(x), 1))
        if len(y) != len(x):
            return None
        J_elem = (1 / (2 * len(y))) * (y - x)**2
        return np.asarray(J_elem)

    def cost_(self, x, y):
        if len(y) != len(x):
            return None
        #J_value = np.square(np.subtract(y, y_hat)).mean()
        return self.cost_elem_(x, y).sum()

    def fit_(self, x, y):
        theta2 = self.theta.astype(float)
        for i in range (0, self.max_iter):
            J = cost_(x, y)
            #print("ARR: ", theta2[0] - (J[0] * alpha))
            theta2[0] /= theta2[0] - (self.alpha * J[0])
            theta2[1] /= theta2[1] - (self.alpha * J[1])
        return theta2

    def plot(self, x, y, theta):
        plt.title('Matplotlib')
        plt.xlabel('Quantity of blue pill (in mg)')
        plt.ylabel('Space driving score')
        #y_pred = theta[0] + theta[1] * x 
        plt.scatter(x, self.y, color = "blue", label="Spredict(Pills)")
        plt.scatter(x, y, color = "green", label="Strue(Pills)")
        plt.plot(x, y, '--g', label="Spredict(Pills)")
        plt.legend(loc='upper right')
        plt.show()

    def mse_(self, x, y):
        return np.sqrt(((x - self.y_hat)**2).mean())

if __name__ == "__main__":
    data = pd.read_csv("are_blue_pills_magics.csv")

    Xpill = np.array(data["Micrograms"]).reshape(-1,1)
    Yscore = np.array(data["Score"]).reshape(-1,1)

    linear_model1 = MyLinearRegression(Xpill, Yscore, np.array([[89.0], [-8]]))
    linear_model2 = MyLinearRegression(Xpill, Yscore, np.array([[89.0], [-6]]))

    Y_model1 = linear_model1.predict_(Xpill)
    Y_model2 = linear_model2.predict_(Xpill)

    print(linear_model1.mse_(Xpill, Yscore))
    print(mean_squared_error(Yscore, Y_model1))
    print(linear_model2.mse_(Xpill, Yscore))
    print(mean_squared_error(Yscore, Y_model2))



