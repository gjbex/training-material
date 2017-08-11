'''Module containing function for computing Julia sets'''

from numba import guvectorize, void, complex128, int32, float64


@guvectorize([void(complex128[:], float64[:], int32[:], int32[:])],
           '(n),(),()->(n)')
def julia_set(domain, max_norm, max_iters, iterations):
    for i, z in enumerate(domain):
        iterations[i] = 0
        while (iterations[i] <= max_iters[0] and
               z.real*z.real + z.imag*z.imag <= max_norm[0]*max_norm[0]):
            z = z**2 - 0.622772 + 0.42193j
            iterations[i] += 1
