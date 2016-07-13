#!/usr/bin/env python

from argparse import ArgumentParser
import numpy as np
import time


def init_julia(re, im, n):
    '''Initialize the complex domain.

    Positional arguments:
    re -- minimum and maximum real value as 2-tuple
    im -- minimum and maximum imaginary value as 2-tuple
    n -- number of real and imaginary points as 2-tuple
    '''
    re_vals, im_vals = np.meshgrid(
            np.linspace(re[0], re[1], n[0]),
            np.linspace(im[0], im[1], n[1])
            )
    domain = re_vals + im_vals*1j
    return domain.flatten()


def julia_set(domain, iteratons, max_norm, max_iters):
    '''Compute the Julia set on a complex domain.

    Positional arguments:
    domain -- complex domain to compute a 1-D array
    iterations -- number of iterations as a 1-D array
    max_norm -- maximum complex norm to iterate to.
    max_iters -- maximum number of iterations
    '''
    for i in range(len(domain)):
        z = domain[i]
        while iterations[i] <= max_iters and np.absolute(z) <= max_norm:
            z = z**2 - 0.622772 + 0.42193j
            iterations[i] += 1
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
    domain = init_julia(
            (options.re_min, options.re_max),
            (options.im_min, options.im_max),
            (options.n_re, options.n_im)
            )
    iterations = np.zeros(options.n_re*options.n_im, dtype=int)
    start_time = time.time()
    julia_set(domain, iterations, options.max_norm, options.max_iters)
    end_time = time.time()
    print('compute time = {0:.6f s}'.format(end_time - start_time))
    if options.show:
        import matplotlib.pyplot as plt
        plt.imshow(iterations.reshape(options.n_re, options.n_im))
        plt.show()
