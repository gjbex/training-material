#!/usr/bin/env python

from itertools import accumulate
from operator import add, mul, concat

if __name__ == '__main__':
    data = range(10)
    for x in accumulate(data, add):
        print(x)
    for x in accumulate(data[1:], mul):
        print(x)
    for x in ([y] for y in data):
        print(x)
    for x in accumulate(([y] for y in data), concat):
        print(x)
    for fragment in accumulate('hello world!', concat):
        print(fragment)
