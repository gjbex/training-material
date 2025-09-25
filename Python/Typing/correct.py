#!/usr/bin/env python

import sys


def fib(n: int) -> int:
    return 1 if n in {0, 1} else fib(n - 1) + fib(n - 2)

if __name__ == '__main__':
    n = int(sys.argv[1]) # type: int
    print(fib(n))
