'''Module containing function for computing Julia sets'''

import numpy as np


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


def julia_set(domain, iterations, max_norm, max_iters):
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
