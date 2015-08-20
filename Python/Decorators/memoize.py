#!/usr/bin/env python


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
    if n < 2:
        return 1
    else:
        return fib_memoized(n - 1) + fib_memoized(n - 2)


def fib(n):
    if n < 2:
        return 1
    else:
        return fib(n - 1) + fib(n - 2)


def execute(func, n_max):
    values = []
    start = datetime.now()
    for n in range(n_max):
        values.append(func(n))
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
    print('non-memoized:\t\t{0:.6f} s'.format(delta_fib))
    print('memoized:\t\t{0:.6f} s'.format(delta_fib_memoized))
