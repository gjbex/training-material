#!/usr/bin/env python

import math


def is_prime(n):
    for i in range(2, round(math.sqrt(n)) + 1):
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
    for n in next_prime():
        print(n)

if __name__ == '__main__':
    main()
