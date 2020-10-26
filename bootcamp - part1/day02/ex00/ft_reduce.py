#!/usr/bin/python3

def afficher(a, b):
    print("Entrée :", a, b)
    print("Sortie :", a + b)
    return a + b


def ft_reduce(function_to_apply, list_of_inputs):
    if isinstance(list_of_inputs, tuple) or isinstance(list_of_inputs, list):
        l1 = list_of_inputs[0]
        for x in range(0, len(list_of_inputs)):
            l1 = function_to_apply(l1, list_of_inputs[x])
        return l1
    elif isinstance(list_of_inputs, dict):
        l0 = list(list_of_inputs.keys())
        l2 = list_of_inputs[l0[0]]
        for x in list_of_inputs:
            l2 = function_to_apply(l2, list_of_inputs[x])
        return l2
    else:
        print("REDUCE: NOT ITERABLE OR IMPLEMENTED")
        exit()


if __name__ == "__main__":
    print("==========> FT_REDUCE <==========\n")

    l1 = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    res = ft_reduce(afficher, l1)
    print("\nLIST Résultat final", res)
    print("\n")

    dico = {
       'a': 1,
       'b': 2,
       'c': 3,
       'd': 4,
       'e': 5,
       'f': 6
    }
    res = ft_reduce(afficher, dico)
    print("\nDICO Résultat", res)

    print("\nDICO Résultat", ft_reduce(lambda x, y: x * y, [1, 2, 3, 4, 5, 6]))
