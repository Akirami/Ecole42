#!/usr/bin/python3

import datetime


class Book:
    def __init__(self, name, recipes_list):
        self.name = name
        self.last_update = ""
        self.creation_date = datetime.datetime.now()
        self.recipes_list = recipes_list

    def __str__(self):
        """Return the string to print with the book info"""
        txt = ""
        desc = ""
        for st in self.recipes_list:
            desc += "  " + st.name + "\n"
        txt += " Cookbook %s contains the recipes:\n%s" % (self.name, desc)
        return txt

    def get_recipe_by_name(self, name):
        """Print a recipe with the name`name`and return the instance"""
        sorted = recipes_list.sort()
        return sorted

    def get_recipes_by_types(self, recipe_type):
        """Get all recipe names for a given recipe_type """
        new_l = []
        li = [r for r in self.recipes_list if r.recipe_type == recipe_type]
        for x in li:
            new_l.append(x.name)
        return new_l

    def add_recipe(self, recipe):
        """Add a recipe"""
        result = isinstance(recipe.cooking_lvl, int)
        if result == 0:
            print("cooking_lvl is not an int.")
            print("\n Closing book.")
            exit()
        result = isinstance(recipe.cooking_time, int)
        if result == 0:
            print("cooking_time is not an int.")
            print("\n Closing book.")
            exit()
        result = isinstance(recipe.ingredients, list)
        if result == 0:
            print("recipes_list is not a list.")
            print("\n Closing book.")
            exit()
        self.last_update = datetime.datetime.now()
        self.recipes_list.append(recipe)
