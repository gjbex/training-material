#!/usr/bin/env python

import collections
import string
import sys


def count_chars(line, counter):
    '''count the alphabetical characters in the given line'''
    for character in line:
        if character in string.ascii_letters:
            counter[character] += 1

if __name__ == '__main__':
    counter = collections.Counter()
    for line in sys.stdin:
        count_chars(line, counter)
    for letter, count in counter.items():
        print('{0}: {1:d}'.format(letter, count))
    print('most common:')
    for letter, count in counter.most_common(3):
        print('{0}: {1:d}'.format(letter, count))
