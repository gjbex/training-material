#!/usr/bin/env python

from argparse import ArgumentParser
import numpy as np
import sys
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
    arg_parser.add_argument('--implementation', default='python',
                            choices=['python', 'ufunc'],
                            help='implementation to use')
    options = arg_parser.parse_args()
    domain = init_julia(
            (options.re_min, options.re_max),
            (options.im_min, options.im_max),
            (options.n_re, options.n_im)
    )
    if options.implementation == 'python':
        from julia_python import julia_set
        iterations = np.zeros(options.n_re*options.n_im, dtype=np.int32)
        start_time = time.time()
        julia_set(domain, iterations, options.max_norm, options.max_iters)
        end_time = time.time()
        if options.show:
            import matplotlib.pyplot as plt
            plt.imshow(np.log1p(iterations.reshape(options.n_re, options.n_im)))
            plt.show()
    elif options.implementation == 'ufunc':
        from julia_ufunc import julia_set
        start_time = time.time()
        iterations = julia_set(domain.reshape(options.n_re, options.n_im),
                               options.max_norm, options.max_iters)
        end_time = time.time()
        if options.show:
            import matplotlib.pyplot as plt
            plt.imshow(np.log1p(iterations))
            plt.show()
    else:
        msg = '{0} version not implemented\n'
        sys.stderr.write(msg.format(options.implementation))
        sys.exit(1)
    print('compute time = {0:.6f} s'.format(end_time - start_time))
