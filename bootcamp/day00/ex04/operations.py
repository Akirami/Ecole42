#!/usr/bin/python3

import sys


def print_error():
    print("Usage: python operations.py <number1> <number2>")
    print("Example:")
    print("    python operations.py 10 3")
    exit()


def print_operations(x, y):
    print("Sum:          %d" % (x + y))
    print("Difference:   %d" % (x - y))
    print("Product:      %d" % (x * y))
    if y != 0:
        print("Quotient:     %d" % (x / y))
    else:
        print("ERROR (div by zero)")
    if y != 0:
        print("Remainer:     %d" % (x % y))
    else:
        print("ERROR (modulo by zero)")


if __name__ == "__main__":
    if len(sys.argv) == 1:
        print_error()
        exit()
    if not sys.argv[1].isdigit():
        print("InputError: only numbers.\n")
        print_error()
    if not sys.argv[2].isdigit():
        print("InputError: only numbers.\n")
        print_error()
    if (len(sys.argv) > 3):
        print("Too many arguments.\n")
        print_error()
    code1 = sys.argv[1]
    code2 = sys.argv[2]
    try:
        arg1 = int(code1)
    except ValueError:
        print("InputError: only numbers.\n")
        print_error()
    try:
        arg2 = int(code2)
    except ValueError:
        print("InputError: only numbers.\n")
        print_error()
    print_operations(int(code1), int(code2))
