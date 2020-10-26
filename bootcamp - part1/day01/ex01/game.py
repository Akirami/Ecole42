#!/usr/bin/python3


class GotCharacter:
    def __init__(self, first_name, is_alive=True):
        self.first_name = first_name
        self.is_alive = is_alive

    def __str__(self):
        """Return the string to print with the recipe info"""
        txt = "Name: " + self.first_name
        txt += " Is Alive?: %s\n" % (self.is_alive)
        return txt


class Stark(GotCharacter):
    """A class representing the Stark family. Or when\
    bad things happen to good people."""
    def __init__(self, first_name=None, is_alive=True):
        super().__init__(first_name=first_name, is_alive=is_alive)
        self.family_name = "Stark"
        self.house_words = "Winter is Coming"

    def print_house_words(self):
        print(self.house_words)

    def die(self):
        self.is_alive = False
