#!/usr/bin/python3

import sys

languages = {
    'Python': 'Guido van Rossum',
    'Ruby': 'Yukihiro Matsumoto',
    'PHP': 'Rasmus Lerdorf',
}

if __name__ == "__main__":
    for lang in languages.items():
        print(lang[0], "was created by", lang[1])
