#!/usr/bin/env python

import functools
import operator

if __name__ == '__main__':
    for i in range(0, 11):
        print(i, functools.reduce(operator.mul, range(1, i + 1), 1))
