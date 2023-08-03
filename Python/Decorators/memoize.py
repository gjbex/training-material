#!/usr/bin/env python

from functools import lru_cache


def memoize(f):
    cache = {}

    def wrapper(n):
        if n not in cache:
            cache[n] = f(n)
        return cache[n]
    wrapper.__name__ = f.__name__
    return wrapper


@memoize
def fib_memoized(n):
    return 1 if n < 2 else fib_memoized(n - 1) + fib_memoized(n - 2)


@lru_cache(100)
def fib_lru_cache(n):
    return 1 if n < 2 else fib_lru_cache(n - 1) + fib_lru_cache(n - 2)


def fib(n):
    return 1 if n < 2 else fib(n - 1) + fib(n - 2)


def execute(func, n_max):
    start = datetime.now()
    values = [func(n) for n in range(n_max)]
    delta = datetime.now() - start
    for n in range(n_max):
        print('{0}({1}) = {2}'.format(func.__name__, n, values[n]))
    delta_time = float(delta.seconds) + 1.0e-6*float(delta.microseconds)
    print('{0}: {1:.6f} s'.format(func.__name__, delta_time))
    return delta_time

if __name__ == '__main__':
    from argparse import ArgumentParser
    from datetime import datetime

    arg_parser = ArgumentParser(description='compare memoized versus '
                                            'non-memooized')
    arg_parser.add_argument('n_max', type=int, help='maximum n value')
    options = arg_parser.parse_args()
    delta_fib = execute(fib, options.n_max)
    delta_fib_memoized = execute(fib_memoized, options.n_max)
    delta_fib_lru_cache = execute(fib_lru_cache, options.n_max)
    print('non-memoized:\t\t{0:.6f} s'.format(delta_fib))
    print('memoized:\t\t{0:.6f} s'.format(delta_fib_memoized))
    print('lru_cache:\t\t{0:.6f} s'.format(delta_fib_lru_cache))
