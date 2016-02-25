def average(data, m=0, n=None):
    if n is None:
        n = len(data)
    return _average(memoryview(data), m, n)

def average_no_except(data, m=0, n=None):
    if n is None:
        n = len(data)
    return _average_no_except(memoryview(data), m, n)

cdef double _average(data, int m=0, int n=-1) except? -1.0:
    cdef int i
    cdef double mean = 0.0
    for i in range(m, n):
        mean += data[i]
    return mean/(n - m + 1)

cdef double _average_no_except(data, int m=0, int n=-1):
    cdef int i
    cdef double mean = 0.0
    for i in range(m, n):
        mean += data[i]
    return mean/(n - m + 1)
