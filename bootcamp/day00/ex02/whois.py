#!/usr/bin/python3

import sys


def print_number_type(num):
    if num == 0:
        print("I'm zero")
        exit()
    if num % 2 == 0:
        print("I'm even.")
    else:
        print("I'm odd.")


if __name__ == "__main__":
    if len(sys.argv) == 1:
        exit()
    elif (len(sys.argv) > 2):
        print("Error.")
        exit()
    code = sys.argv[1].lstrip('-')
    if not code.isdigit():
        print("Error.")
        exit()
    print_number_type(int(code))
