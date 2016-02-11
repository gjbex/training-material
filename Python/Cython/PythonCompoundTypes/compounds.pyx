def sum_list(list double, data):
    cdef int i
    cdef double total = 0.0
    for i in range(len(data)):
        total += data[i]
    return total
