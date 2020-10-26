#!/usr/bin/python3
from decimal import Decimal


t = (0, 4, 132.42222, 10000, 12345.67)

if __name__ == "__main__":
    print("day_0%s, ex_0\
        %s : %.2f, %.2e, %2.2e" % (t[0], t[1], t[2], t[3], t[4]))
