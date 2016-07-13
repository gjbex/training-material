#!/usr/bin/env python

from argparse import ArgumentParser
import numpy as np


def julia(z):
    '''Complex function to iterate.'''
    return z**2 - 0.622772 + 0.42193j


def update_domain(domain, iterations, max_norm):
    domain[np.absolute(domain) <= max_norm] = julia(domain)
    iterations[np.absolute(domain) <= max_norm] += 1


def julia_set(re, im, n, max_norm, max_iters):
    '''Compute the Julia set on a complex domain.

    Positional arguments:
    re -- limits of the real part of the domain as 2-tuple
    im -- limits of the complex part of the domain as 2-tuple
    n -- number of points on the real and the imaginary axis as tuple
    max_norm -- maximum complex norm to iterate to.
    max_iters -- maximum number of iterations
    '''
    re_vals, im_vals = np.meshgrid(
            np.linspace(re[0], re[1], n[0]),
            np.linspace(im[0], im[1], n[1])
            )
    domain = re_vals + im_vals*1j
    iterations = np.zeros(n, dtype=int)
    for iter_nr in max_iters:
        update_domain(domain, iterations, max_norm)
    return iterations

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='Compute julia set')
    arg_parser.add_argument('--re_min', type=float, default=-1.8,
                            help='minimum real value')
    arg_parser.add_argument('--re_max', type=float, default=1.8,
                            help='maximum real value')
    arg_parser.add_argument('--im_min', type=float, default=-1.8,
                            help='minimum imaginary value')
    arg_parser.add_argument('--im_max', type=float, default=1.8,
                            help='maximum imaginary value')
    arg_parser.add_argument('--max_norm', type=float, default=2.0,
                            help='maximum complex norm for z')
    arg_parser.add_argument('--n_re', type=int, default=100,
                            help='number of points on the real axis')
    arg_parser.add_argument('--n_im', type=int, default=100,
                            help='number of points on the imaginary axis')
    arg_parser.add_argument('--max_iters', type=int, default=300,
                            help='maximum number of iterations')
    arg_parser.add_argument('--show', action='store_true',
                            help='show plot')
    options = arg_parser.parse_args()
    iterations = julia_set(
            (options.re_min, options.re_max),
            (options.im_min, options.im_max),
            (options.n_re, options.n_im),
            options.max_norm, options.max_iters
            )
    if options.show:
        import matplotlib.pyplt as plt
        plt.imshow(iterations)
        plt.show()
