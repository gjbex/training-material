def squares(int n):
    cdef list sqrs = []
    cdef int i = 0
    while i < n:
        sqrs.append(i**2)
        incr(&i)
    return sqrs

cdef void incr(int *i):
    i[0] += 1
