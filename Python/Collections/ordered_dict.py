#!/usr/bin/env python

import collections
import string
import sys


def count_chars(line, counter):
    '''count the alphabetical characters in the given line'''
    for character in line:
        if character in string.ascii_letters:
            character = character.lower()
            if character not in counter:
                counter[character] = 0
            counter[character] += 1

if __name__ == '__main__':
    counter = collections.OrderedDict()
    for line in sys.stdin:
        count_chars(line, counter)
    for letter, count in counter.items():
        print('{0}: {1:d}'.format(letter, count))
