#!/usr/bin/env python

import math


class InvalidArgumentException(Exception):
    '''Exception raised when an illigal agrument is passed to a function'''


def fib(n):
    '''compute the nth Fibonacci number iteratively'''
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


def pi(n):
    '''copmute pi using a quadrature method'''
    if n < 1:
        raise InvalidArgumentException('number of integration points '
                                       'should at least be 1')
    sum = 0.0
    x = 0.0
    delta_x = 1.0/n
    while x <= 1.0:
        sum += 4.0/(1.0 + x**2)
        x += delta_x
    return sum/n


def is_prime(n):
    '''returns True when the given number of prime, false otherwise'''
    if n < 0:
        raise InvalidArgumentException('number should be positive')
    factor = 2
    while factor <= int(math.sqrt(n)):
        if n % factor == 0:
            return False
        factor += 1
    return True
# correct implementation for n >= 0
#    return n > 1
# for n < 0, an exception might be thrown


def primes(n):
    '''returns a list of primes less than or equal to the given nuber'''
    prime_list = []
    for i in range(n + 1):
        if is_prime(i):
            prime_list.append(i)
    return prime_list


if __name__ == '__main__':
    for i in range(5):
        print('fib({0:d}) = {1:d}'.format(i, fib(i)))
