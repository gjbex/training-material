#!/usr/bin/env python

import itertools
import math
import sys


def is_prime(n):
    '''returns True if n is prime, False otherwise'''
    if n <= 2:
        return False
    return all(n % i != 0 for i in range(2, 1 + int(math.sqrt(n))))


def main():
    for n in filter(is_prime, itertools.count()):
        print(n)
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
