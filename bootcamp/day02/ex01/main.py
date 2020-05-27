#!/usr/bin/python3

import inspect


def what_are_the_vars(*args, **kwargs):
    bound_args = inspect.signature(what_are_the_vars).bind(*args, **kwargs)
    bound_args.apply_defaults()
    print(dict(bound_args.arguments))

    dico = dict(bound_args.arguments)

    print("YOLO", dico['kwargs'])

    c = ObjectC

    for x in range(len(dico['args'])):
        setattr(c, 'x' + str(x), dico['args'][x])
    for k, v in kwargs.items():
        setattr(c, k, dico['kwargs'][k])

    return c


class ObjectC(object):
    def __init__(self):
        pass


def doom_printer(obj):
    if obj is None:
        print("ERROR")
        print("end")
        return
    for attr in dir(obj):
        if attr[0] != '_':
            value = getattr(obj, attr)
            print("{}: {}".format(attr, value))
    print("end")


if __name__ == "__main__":
    obj = what_are_the_vars(7)
    doom_printer(obj)
    obj = what_are_the_vars("ft_lol", "Hi")
    doom_printer(obj)
    obj = what_are_the_vars()
    doom_printer(obj)
    obj = what_are_the_vars(12, "Yes", [0, 0, 0], a=10, hello="world")
    doom_printer(obj)
    obj = what_are_the_vars(42, a=10, var_0="world")
    doom_printer(obj)
