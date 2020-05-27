#!/usr/bin/python3

def addition(n):
    return n + n


def ft_map(function_to_apply, list_of_inputs):
    l1 = []
    if isinstance(list_of_inputs, tuple) or isinstance(list_of_inputs, list):
        for x in list_of_inputs:
            l1.append(function_to_apply(x))
    elif isinstance(list_of_inputs, dict):
        for v in list_of_inputs:
            l1.append(function_to_apply(v))
    else:
        print("MAP: NOT ITERABLE OR IMPLEMENTED")
        exit()
    return (l1)


def ft_reduce(function_to_apply, list_of_inputs):
    pass


if __name__ == "__main__":
    print("==========> FT_MAP <==========\n")

    result = []
    numbers1 = [1, 2, 3, 4]
    numbers2 = (1, 2, 3, 4)
    numbers3 = {'a': 1, 'b': 2, 'c': 3}

    result = ft_map(addition, numbers1)
    print("LIST: ", result)
    result = ft_map(lambda x: x + x, numbers1)
    print("lLIST: ", list(result))

    result = ft_map(addition, numbers2)
    print("TUPL: ", list(result))
    result = ft_map(lambda x: x + x, numbers2)
    print("lTUPL: ", list(result))

    result = ft_map(addition, numbers3)
    print("DICT: ", list(result))
    result = ft_map(lambda x: x + x, numbers3)
    print("DICT: ", list(result))
