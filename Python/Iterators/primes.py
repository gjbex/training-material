#!/usr/bin/env python

import math
import sys


def is_prime(n):
    for i in range(2, int(math.sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True


def next_prime():
    yield 2
    n = 3
    while True:
        if is_prime(n):
            yield n
        n += 1


def main():
    if len(sys.argv) > 1:
        max_nr = int(sys.argv[1])
    else:
        max_nr = None
    for n in next_prime():
        if max_nr and n > max_nr:
            break
        print(n)

if __name__ == '__main__':
    main()
