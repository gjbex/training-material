#!/usr/bin/env python

from argparse import ArgumentParser
import sys
import numpy as np


def linear(x, a=0.4, b=1.2):
    return a*x + b

arg_parser = ArgumentParser(description='create linear data with noise')
arg_parser.add_argument('n', type=int, default=5, help='number of points')
arg_parser.add_argument('--x_min', type=float, default=0.0,
                        help='minimum x-value')
arg_parser.add_argument('--x_max', type=float, default=1.0,
                        help='maximum x-value')
arg_parser.add_argument('--a', type=float, default=0.4,
                        help='slope in a*x + b')
arg_parser.add_argument('--b', type=float, default=1.2,
                        help='intercept in a*x + b')
arg_parser.add_argument('--sigma', type=float, default=0.25,
                        help='noise level')
arg_parser.add_argument('--out', help='name of output file')
options = arg_parser.parse_args()

names = 'x,y'
x = np.linspace(options.x_min, options.x_max, options.n)
f = np.vectorize(linear)
y = f(x, options.a, options.b) + options.sigma*np.random.randn(len(x))

if options.out:
    out = open(options.out, 'w')
else:
    out = sys.stdout
out.write(names + '\n')
for i in range(len(x)):
    out.write('{x:.7e},{y:.7e}\n'.format(x=x[i], y=y[i]))
if options.out:
    out.close()
