from functools import reduce
import numpy as np


def cons(dims):
    array = np.empty(reduce(lambda x, y: x*y, dims, 1))
    _cons(memoryview(array))
    return array.reshape(dims)

cdef void _cons(mv):
    cdef int i
    for i in range(mv.nbytes//mv.itemsize):
        mv[i] = <double> i
