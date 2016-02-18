from cython cimport boundscheck, wraparound


def array_sum(a):
    return _array_sum(memoryview(a))


cdef double _array_sum(double[:,::1] mem_view):
    cdef double total = 0.0
    cdef m = mem_view.shape[0]
    cdef n = mem_view.shape[1]
    cdef int i, j
    with boundscheck(False), wraparound(False):
        for i in range(m):
            for j in range(n):
                total += mem_view[i, j]
    return total
