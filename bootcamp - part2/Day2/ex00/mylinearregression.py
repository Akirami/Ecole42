#!/usr/bin/python3

import numpy as np

class MyLinearRegression():
    def __init__(self,  thetas):
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
        x = self.add_intercept(x)
        return x.dot(self.thetas)

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

    def fit_(self, x, y, alpha=0.001, n_cycle=1000):
        theta2 = self.thetas.astype(float)
        for i in range (0, n_cycle):
            J = self.cost_(x, y)
            print("ARR: ",J)
            theta2[0] /= theta2[0] - (alpha * J[0])
            theta2[1] /= theta2[1] - (alpha * J[1])
        return theta2


if __name__ == "__main__":
    x = np.array([[12.4956442], [21.5007972], [31.5527382], [48.9145838], [57.5088733]])
    y = np.array([[37.4013816], [36.1473236], [45.7655287], [46.6793434], [59.5585554]])

    lr1 = MyLinearRegression([2, 0.7])

    print("PRED: ", lr1.predict_(x))
    print("COSTELEM: ", lr1.cost_elem_(lr1.predict_(x), y))
    print("COST: ", lr1.cost_(lr1.predict_(x), y))

    print("\n")
    lr2 = MyLinearRegression([0, 0])
    #print(lr2.fit_(x, y, alpha=5e-8, n_cycle = 1500))
    print("TET: ", lr2.thetas)
    print("PRE: ", lr2.predict_(x))
    print("COSTELEM: ", lr2.cost_elem_(lr1.predict_(x), y))
    print("COST: ", lr2.cost_(lr1.predict_(x), y))

   # Example pété, enoncé faux, ils ont qu'à faire leur taf, je passe à la suite





