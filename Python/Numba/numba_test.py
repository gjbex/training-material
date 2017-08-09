#!/usr/bin/env python

from datetime import datetime
from numba import jit
import numpy as np


@jit
def jit_exp(x):
    n = len(x)
    y = np.empty(n)
    for i in range(n):
        tmp = np.exp(-x[i]**2)
        y[i] = 0.0 if tmp < 0.5 else tmp
    return y


def nonjit_exp(x):
    n = len(x)
    y = np.empty(n)
    for i in range(n):
        tmp = np.exp(-x[i]**2)
        y[i] = 0.0 if tmp < 0.5 else tmp
    return y


def vec_exp(x):
    clamp = np.vectorize(lambda x: 0.0 if x < 0.5 else x)
    return clamp(np.exp(-x**2))


def filter_exp(x):
    y = np.exp(-x**2)
    y[y < 0.5] = 0.0
    return y

if __name__ == '__main__':
    from argparse import ArgumentParser

    arg_parser = ArgumentParser(description='times array manupilation')
    arg_parser.add_argument('--n', type=int, default=100001,
                            help='array size')
    arg_parser.add_argument('--loops', type=int, default=100,
                            help='number of loops')
    options = arg_parser.parse_args()
    functions = [filter_exp, vec_exp, nonjit_exp, jit_exp]
    x = np.linspace(-2.0, 2.0, options.n)
    for func in functions:
        print(func.__name__)
        time = None
        for _ in range(options.loops):
            start = datetime.now()
            y = func(x)
            end = datetime.now()
            if time:
                time += end - start
            else:
                time = end - start
        microseconds = (time.seconds*1.0e6 + time.microseconds)/options.loops
        print('{0:-12.0f} microseoncs'.format(microseconds))
