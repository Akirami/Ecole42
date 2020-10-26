#!/usr/bin/python3

import sys


def reverse_slicing(s):
    return s[::-1]


if __name__ == "__main__":
    i = 1
    while i < len(sys.argv):
        print('', reverse_slicing(str(sys.argv[i]).swapcase()))
        i = i + 1
