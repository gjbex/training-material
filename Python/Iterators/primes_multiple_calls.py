#!/usr/bin/env python

import math
import sys


def is_prime(n):
    for i in range(2, int(math.sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True


def next_prime():
    n = 2
    while True:
        if is_prime(n):
            yield n
        n += 1


def main():
    for i, n in enumerate(next_prime()):
        if n > 10:
            break
        print(f'{i + 1}: {n}')
    for i, n in enumerate(next_prime()):
        if n > 10:
            break
        print(f'{i + 1}: {n}')

if __name__ == '__main__':
    main()
