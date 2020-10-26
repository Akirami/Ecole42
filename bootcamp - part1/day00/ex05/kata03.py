#!/usr/bin/python3

phrase = "The right format"

if __name__ == "__main__":
    str = phrase.rjust(42, "-")
    print(str, end='')
