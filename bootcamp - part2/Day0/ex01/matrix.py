#!/usr/bin/python3

from vector import Vector

def print_error(s):
    print(s)
    exit()

from vector import Vector


class Matrix():
    """docstring for Matrix."""

    def __init__(self, values, shap=None):
        if (isinstance(values, list)):
            if (shap is not None):
                self.shape = shap
            else:
                self.shape = (len(values), len(values[0]))
            for x in values:
                if (isinstance(x, list) and self.shape[1] == len(x)
                        and self.shape[0] == len(values)):
                    for y in x:
                        if not isinstance(y, float):
                            self.my_exit("Matrix list values must be floats")
                        else:
                            self.data = values
                else:
                    self.my_exit("Matrix values must be list of floats"
                                 " of same size or bad given shape")
            # pprint(self.data)
            # print(self.shape)
        elif (isinstance(values, tuple) and len(values) == 2
              and isinstance(values[0], int) and isinstance(values[1], int)):
            self.shape = values
            self.data = []
            for i in range(values[0]):
                self.data += [[0 for j in range(values[1])]]
            # pprint(self.data)
            # print(self.shape)
        else:
            self.my_exit(
                f"Bad value or bad type for values: ({values})")

    def __str__(self):
        txt = (f"({self.__class__.__name__}{self.data})")
        return txt

    def __repr__(self):
        txt = (f"{self.__class__.__name__}({self.data}) size: {self.shape}")
        return txt

    def __add__(self, other):
        if isinstance(other, Matrix) and self.shape == other.shape:
            ret = Matrix(self.shape)
            for x in range(self.shape[0]):
                ret.data[x] = [self.data[x][j] + other.data[x][j]
                               for j in range(self.shape[1])]
            return ret
        elif isinstance(other, Vector) and self.shape[1] == other.size:
            ret = Matrix(self.shape)
            for x in range(self.shape[0]):
                ret.data[x] = [self.data[x][j] + other.values[j]
                               for j in range(self.shape[1])]
            return ret
        else:
            self.my_return(
                f"{other} not a Matrix or Vector or 2 matrix/"
                "vector not same size")

    def __radd__(self, other):
        return self.__add__(other)

    def __sub__(self, other):
        if isinstance(other, Matrix) and self.shape == other.shape:
            ret = Matrix(self.shape)
            for x in range(self.shape[0]):
                ret.data[x] = [self.data[x][j] - other.data[x][j]
                               for j in range(self.shape[1])]
            return ret
        elif isinstance(other, Vector) and self.shape[1] == other.size:
            ret = Matrix(self.shape)
            for x in range(self.shape[0]):
                ret.data[x] = [self.data[x][j] - other.values[j]
                               for j in range(self.shape[1])]
            return ret
        else:
            self.my_return(
                f"{other} not a Matrix or Vector or 2 matrix/"
                "vector not same size")

    def __rsub__(self, other):
        return other.__sub__(self)

    def __truediv__(self, other):
        if isinstance(other, (int, float)) and other != 0:
            ret = Matrix(self.shape)
            for x in range(self.shape[0]):
                ret.data[x] = [self.data[x][j] / other
                               for j in range(self.shape[1])]
            return ret
        else:
            self.my_return(f"{other} not a int/float or zero")

    def __rtruediv__(self, other):
        if isinstance(other, (int, float)) and other != 0:
            # print("Scalar detected")
            return self.__mul__(1 / other)
        self.my_return(f"{other} not a Int/float or zero")

    def __mul__(self, other):
        if isinstance(other, (int, float)):
            ret = Matrix(self.shape)
            for x in range(self.shape[0]):
                ret.data[x] = [self.data[x][j] * other
                               for j in range(self.shape[1])]
            return ret
        elif isinstance(other, Vector) and self.shape[1] == other.size:
            # print("Vector detected")
            ret = Vector(self.shape[0])
            for x in range(self.shape[0]):
                ret.values[x] = [self.data[x][j] * other.values[j]
                                 for j in range(self.shape[1])]
                ret.values[x] = sum(ret.values[x])
            return ret
        elif isinstance(other, Matrix) and self.shape[1] == other.shape[0]:
            # print("Matrix detected")
            ret = Matrix(self.shape)
            temp = Vector((other.shape[1]))
            # print(other)
            # print(self)
            for x in range(other.shape[1]):
                temp.values[x] = [other.data[j][x]
                                  for j in range(other.shape[0])]
            # print(f"ap :{temp.values}")

            for x in range(self.shape[0]):
                ret.data[x] = (self.__mul__(Vector(temp.values[x]))).values
                # ret.data[x] = sum(ret.data[x])
                # print(f"{x} : {ret.data[x]}")
            return ret
        else:
            self.my_return(
                f"{other} not a Matrix or Vector or Int/float,or 2 matrix/vector not same size")

    def __rmul__(self, other):
        return self.__mul__(other)

    def my_return(self, str):
        print(str)
        return()

    def my_exit(self, str):
        print(str)
        exit()

if __name__ == "__main__":
    m1 = Matrix([[0.0, 1.0, 2.0, 3.0],[0.0, 2.0, 4.0, 6.0]])
    m2 = Matrix([[0.0, 1.0],[2.0, 3.0],[4.0, 5.0],[6.0, 7.0]])
    print(m1 * m2)

    v1 = Vector([0.0, 1.0, 2.0, 3.0])
    print(m1 * v1)