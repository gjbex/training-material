'''Module containing function for computing Julia sets'''

import numpy as np


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
