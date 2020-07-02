#!/usr/bin/python3


def print_error(s):
    print(s)
    exit()


class Vector:
    def __init__(self, values=None, size=None):
        self.values = []
        if (isinstance(values, list)):
            self.values = values
            self.size = len(self.values)
        if (isinstance(values, tuple)):
            for i in range(values[0], values[1]):
                self.values.append(i)
            self.size = len(self.values)
        if (isinstance(values, int)):
            for i in range(0, values):
                self.values.append(i)
            self.size = values

    def __str__(self):
        desc = "Vector[("
        for st in self.values:
            desc += str(st) + ", "
        desc = desc[:-2]
        desc += ")]"
        return desc

    def __add__(self, other):
        print("ADD")
        if not isinstance(other, Vector):
            print_error("One arg is not an instance of Vector")
        if not self.size == other.size:
            print_error("Vector have not same size.")
        li = []
        for x in range(0, self.size):
            li.append(self.values[x] + other.values[x])
        lv = Vector(li)
        return lv

    def __sub__(self, other):
        print("SUB")
        if not isinstance(other, Vector):
            print_error("One arg is not an instance of Vector")
        if not self.size == other.size:
            print_error("Vector have not same size.")
        l1 = []
        for x in range(0, self.size):
            l1.append(self.values[x] - other.values[x])
        lv = Vector(l1)
        return lv

    def __truediv__(self, other):
        print("DIV")
        if not isinstance(other, int) and not isinstance(other, float):
            print_error("Can't divide, this is not an int or float")
        if other == 0:
            print_error("Divide by 0 not allowed")
        l1 = []
        for x in range(0, self.size):
            l1.append(self.values[x] / other)
        lv = Vector(l1)
        return lv

    def __mul__(self, other):
        l1 = []
        if isinstance(other, list):
            if not all(isinstance(item, float) for item in other):
                print_error("List contains wrong datas")
        elif not isinstance(other, int) and not\
isinstance(other, float) and not isinstance(other, Vector):
            print_error("Can't multiply, this is not an int, float or Vector")
        if isinstance(other, Vector):
            if not self.size == other.size:
                print_error("Vector have not same size.")
            for x in range(0, self.size):
                l1.append(self.values[x] * other.values[x])
            lv = Vector(l1)
        elif isinstance(other, list):
            if not self.size == len(other):
                print_error("Vector have not same size.")
            for x in range(0, self.size):
                l1.append(self.values[x] * other[x])
            lv = Vector(l1)
        else:
            for x in range(0, self.size):
                l1.append(self.values[x] * other)
            lv = Vector(l1)
        return lv

    def __rmul__(self, other):
        print("rMUL")
        l1 = []
        if isinstance(other, list):
            if not all(isinstance(item, float) for item in other):
                print_error("List contains wrong datas")
        elif not isinstance(other, int) and\
        not isinstance(other, float) and not isinstance(other, Vector):
            print_error("Can't multiply, this is not an int, float or Vector")
        if isinstance(other, Vector):
            if not self.size == other.size:
                print_error("Vector have not same size.")
            for x in range(0, self.size):
                l1.append(self.values[x] * other.values[x])
            lv = Vector(l1)
        elif isinstance(other, list):
            if not self.size == len(other):
                print_error("Vector have not same size.")
            for x in range(0, self.size):
                l1.append(self.values[x] * other[x])
            lv = Vector(l1)
        else:
            for x in range(0, self.size):
                l1.append(self.values[x] * other)
            lv = Vector(l1)
        return lv

    def __rtruediv__(self, other):
        print("rDIV")
        if not isinstance(other, int) and not isinstance(other, float):
            print_error("Can't divide, this is not an int or float")
        if other == 0:
            print_error("Divide by 0 not allowed")
        l1 = []
        for x in range(0, self.size):
            l1.append(self.values[x] / other)
        lv = Vector(l1)
        return lv

    def __radd__(self, other):
        print("rADD")
        l1 = []
        if not self.size == len(other):
            print_error("Vector have not same size.")
        for x in range(0, self.size):
            l1.append(self.values[x] + other[x])
        lv = Vector(l1)
        return lv

    def __rsub__(self, other):
        print("rSUB")
        l1 = []
        if not self.size == len(other):
            print_error("Vector have not same size.")
        for x in range(0, self.size):
            l1.append(self.values[x] - other[x])
        lv = Vector(l1)
        return lv


if __name__ == "__main__":
    v1 = Vector([0.0, 1.0, 2.0, 3.0])
    print(v1)
    v2 = Vector(4)
    print(v2)
    v3 = Vector((3, 10))
    print(v2)

    vz = ([0.0, 1.0, 2.0, 5.0])

    print("ADD", v1 + v2)
    print("SUB", v1 - v2)
    print("DIV", v2 / 2)
    print("MUL", v2 * v1)
    print("MUL", v2 * 10)

    print("rADD", vz + v1)
    print("rSUB", vz - v1)
    print("rMUL", 2 * v2)
    print("rMUL", vz * v2)