#!/usr/bin/python3


def fun(variable):
    letters = ['a', 'e', 'i', 'o', 'u']
    if (variable in letters):
        return True
    else:
        return False


def ft_filter(function_to_apply, list_of_inputs):
    l1 = []
    if isinstance(list_of_inputs, tuple) or isinstance(list_of_inputs, list):
        for x in list_of_inputs:
            result = function_to_apply(x)
            if isinstance(result, bool):
                if result:
                    l1.append(x)
            else:
                print("WRONG FUNCTION RETURN TYPE")
                exit()
    elif isinstance(list_of_inputs, dict):
        for k, v in list_of_inputs.items():
            result = function_to_apply(v)
            if isinstance(result, bool):
                if result:
                    l1.append(v)
            else:
                print("WRONG FUNCTION RETURN TYPE")
                exit()
    else:
        print("FILTER: NOT ITERABLE OR IMPLEMENTED")
        exit()
    return l1


if __name__ == "__main__":
    print("==========> FILTER <==========\n")

    sequence = ['g', 'e', 'e', 'j', 'k', 's', 'p', 'r']
    filtered1 = ft_filter(fun, sequence)
    print("LIST", filtered1)
    seq = [0, 1, 2, 3, 5, 8, 13]
    result = filter(lambda x: x % 2 != 0, seq)
    print(list(result))
    sequence = ('g', 'e', 'e', 'j', 'k', 's', 'p', 'r')
    filtered2 = ft_filter(fun, sequence)
    print("TUPL", filtered2)
    dico = {
       1: 'g',
       2: 'e',
       3: 'i',
       4: 's',
       5: 'x',
       6: 'o'
    }
    filtered3 = ft_filter(fun, dico)
    print("DICO", filtered3)
