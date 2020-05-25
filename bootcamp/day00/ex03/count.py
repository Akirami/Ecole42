#!/usr/bin/python3
from string import punctuation
import os


def text_analyzer(s="", *argv):
    """\nThis function counts the number of upper characters, \
 lower characters, punctuation and spaces in a given text."""
    if len(argv) > 0:
        print("ERROR")
        quit()
    print("SSS ", s)
    if s == "":
        s = input("What is the text to analyse?\n>>")
    print("The text contains %d characters:\n" % (sum(1 for c in s)))
    print("%d upper letters\n" % (sum(1 for c in s if c.isupper())))
    print("%d lower letters\n" % (sum(1 for c in s if c.islower())))
    print("%d punctuation marks\n" % (sum(1 for c in s if c in punctuation)))
    print("%d spaces\n" % (sum(1 for c in s if c.isspace())))
