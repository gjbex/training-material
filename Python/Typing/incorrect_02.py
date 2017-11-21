#!/usr/bin/env python

import sys


def fib(n: int) -> int:
    if n == 0 or n == 1:
        return 1
    else:
        return fib(n - 1) + fib(n - 2)

if __name__ == '__main__':
    n = int(sys.argv[1]) # type: str
    print(fib(n))
