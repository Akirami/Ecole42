#!/usr/bin/python3

import sys


def print_error():
    print("ERROR")
    exit()


def print_filtered(arg1, arg2):
    s = str(arg1).split()
    new_list = [x for x in s if len(x) > arg2]
    print(new_list)


if __name__ == "__main__":
    if not len(sys.argv) == 3:
        print_error()
    code = sys.argv[1]
    code1 = sys.argv[2]
    if sys.argv[1].isdigit():
        print_error()
    try:
        arg2 = int(code1)
    except ValueError:
        print_error()
    print_filtered(code, int(code1))
