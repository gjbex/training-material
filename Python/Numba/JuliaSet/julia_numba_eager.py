'''Module containing function for computing Julia sets'''

from numba import jit, void, int32, float64, complex128


@jit(void(complex128[:], int32[:], float64, int32))
def julia_set(domain, iterations, max_norm, max_iters):
    '''Compute the Julia set on a complex domain.

    Positional arguments:
    domain -- complex domain to compute a 1-D array
    iterations -- number of iterations as a 1-D array
    max_norm -- maximum complex norm to iterate to.
    max_iters -- maximum number of iterations
    '''
    for i, z in enumerate(domain):
        while (iterations[i] <= max_iters and
               z.real*z.real + z.imag*z.imag <= max_norm*max_norm):
            z = z**2 - 0.622772 + 0.42193j
            iterations[i] += 1
