#!/usr/bin/env python

import math
import sys


def is_prime(n):
    return all(n % i != 0 for i in range(2, int(math.sqrt(n)) + 1))


def next_prime():
    yield 2
    n = 3
    while True:
        if is_prime(n):
            yield n
        n += 1


def main():
    max_nr = int(sys.argv[1]) if len(sys.argv) > 1 else None
    for n in next_prime():
        if max_nr and n > max_nr:
            break
        print(n)

if __name__ == '__main__':
    main()
