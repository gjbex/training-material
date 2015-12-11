#!/usr/bin/env python


class InvalidArgumentException(Exception):
    '''Exception raised when an illigal agrument is passed to a function'''


def fib(n):
    if n == 0 or n == 1:
        return 1
    elif n > 1:
        return fib(n - 1) + fib(n - 2)
    else:
        raise InvalidArgumentException('illegal negative argument for fib')


def fib_fast(n):
    if n < 0:
        raise InvalidArgumentException('illegal negative argument for fib')
    a = 1
    b = 1
    while n > 1:
        tmp = a
        a = b + a
        b = tmp
        n -= 1
    return a

if __name__ == '__main__':
    for i in range(5):
        print('fib({0:d}) = {1:d}'.format(i, fib(i)))
