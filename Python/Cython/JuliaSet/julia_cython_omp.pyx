'''Module containing function for computing Julia sets'''

cimport cython
from cython.parallel import prange

def julia_set(domain, iterations, max_norm, max_iters):
    return _julia_set(memoryview(domain), memoryview(iterations),
                      max_norm, max_iters)


@cython.boundscheck(False)
cdef _julia_set(double complex[:] domain, int[:] iterations,
                double max_norm, int max_iters):
    '''Compute the Julia set on a complex domain.

    Positional arguments:
    domain -- complex domain to compute a 1-D array
    iterations -- number of iterations as a 1-D array
    max_norm -- maximum complex norm to iterate to.
    max_iters -- maximum number of iterations
    '''
    cdef int i, length = len(domain)
    cdef complex z
    with nogil:
        for i in prange(length, schedule='guided'):
            z = domain[i]
            while (iterations[i] <= max_iters and
                   z.real*z.real + z.imag*z.imag <= max_norm*max_norm):
                z = z**2 - 0.622772 + 0.42193j
                iterations[i] += 1
