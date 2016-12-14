from cython.parallel import prange
from libc.math cimport sqrt

cpdef double compute_pi(long n):
    cdef double delta = 1.0/n, total_sum = 0.0, x
    cdef long i
    with nogil:
        for i in prange(n, schedule='static'):
            x = -1.0 + i*delta
            total_sum += sqrt(1.0 - x*x)
    return 4.0*total_sum/n
