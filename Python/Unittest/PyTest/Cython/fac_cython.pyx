def fac(int n):
    cdef int i
    cdef int result = 1
    if (n > 1):
        for i in range(2, n + 1):
            result *= i
    return result
