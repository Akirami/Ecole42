#!/usr/bin/python3

import sys

cookbook = {
    "sandwich": {
        "ingredients": ["ham", "bread", "cheese", "tomatoes"],
        "type": "lunch",
        "prep_time": 10,
    },
    "cake": {
        "ingredients": ["flour", "sugar", "eggs"],
        "type": "dessert",
        "prep_time": 60,
    },
    "salad": {
        "ingredients": ["avocado", "arugula", "tomatoes", "spinach"],
        "type": "lunch",
        "prep_time": 15,
    }
}


def print_list():
    print("\nPlease select an option by typing the corresponding number:")
    print("1: Add a recipe")
    print("2: Delete a recipe")
    print("3: Print a recipe")
    print("4: Print the cookbook")
    print("5: Quit")


def print_recipe():
    print("Please enter the recipe's name to get its details:")
    st = input(">> ")
    if st in cookbook:
        print("Recipe for cake:")
        print("Ingredients list: %s" % (cookbook[st]['ingredients']))
        print("To be eaten for %s." % (cookbook[st]['type']))
        print("Takes %s minutes of cooking." % (cookbook[st]['prep_time']))
    else:
        print("%s is not in cookbook" % (st))
    handle_input()


def add_recipe():
    s1 = input("Enter recipe name: >> ")
    s2 = input("Enter ingredients list: >> ")
    s3 = input("Enter recipe type: >> ")
    s4 = input("Enter prep time: >> ")
    try:
        s5 = int(s4)
    except ValueError:
        print("Not a number.")
        print_list()
        handle_input()

    cookbook.update({s1: {
        'ingredients': s2,
        "type": s3,
        "prep_time": s4,
        }
    })
    print("%s added to cookbook." % (s1))
    print_list()
    handle_input()


def delete_recipe():
    s1 = input("Enter recipe name to delete: >> ")
    if s1 in cookbook:
        cookbook.pop(s1, None)
        print("%s deleted." % (s1))
        print_list()
        handle_input()
    else:
        print("%s is not in cookbook" % (s1))
        print_list()
        handle_input()


def print_all_recipes():
    for st in cookbook:
        print(" ---> ", st)
    print_list()
    handle_input()


def handle_input():
    s = input(">> ")
    try:
        if (int(s) < 0 and int(s) > 5):
            print_error()
    except ValueError:
        print_error()
    if int(s) == 5:
        print("\nCookbook closed.")
        exit()
    if int(s) == 1:
        add_recipe()
    if int(s) == 2:
        delete_recipe()
    if int(s) == 3:
        print_recipe()
    if int(s) == 4:
        print_all_recipes()


def print_error():
    print("\nOption does not exist, please type the corresponding number.")
    print("To exit, enter 5")
    handle_input()


if __name__ == "__main__":
    print_list()
    handle_input()
