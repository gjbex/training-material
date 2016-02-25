def sum_list(list data):
    cdef int i, n = len(data)
    cdef double total = 0.0
    for i in range(n):
        total += data[i]
    return total
