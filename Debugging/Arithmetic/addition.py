#!/usr/bin/env python

from argparse import ArgumentParser
import numpy as np

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='illustrate addition accuracy')
    arg_parser.add_argument('--numbers', type=int, default=1000000,
                            help='array size')
    options = arg_parser.parse_args()
    array = 1.0e-16*np.random.uniform(size=options.numbers)
    result1 = 1.0
    result2 = 0.0
    for x in array:
        result1 += x
        result2 += x
    result2 += 1.0
    print(f'1 + sum(x) = {result1}')
    print(f'sum(x) + 1 = {result2}')
    dev = (result2 - result1)/result1
    print(f'relative error = {dev:.3e}')
