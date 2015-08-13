#!/usr/bin/env python

import itertools
import sys


def all_fibonacci():
    n_2 = 1
    n_1 = 1
    for n in itertools.count(1):
        if n == 1 or n == 2:
            yield 1
        else:
            value = n_1 + n_2
            n_2 = n_1
            n_1 = value
            yield value


def main():
    nr_fib = 0
    max_nr_fib = None
    if len(sys.argv) > 1:
        max_nr_fib = int(sys.argv[1])
    for n in all_fibonacci():
        if max_nr_fib and nr_fib >= max_nr_fib:
            break
        nr_fib += 1
        print(n)
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
