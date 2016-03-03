# Numpy
Using `memoryview` it is easy to access data types that expose a buffer
interface for interacting efficiently with the data variables of those
types contain. `numpy` arrays are an example of such a data type.
The example provided here compares run times for computing the sum of
the elements of a 2D array using a pure Python, and Cython implementation
to `np.sum`.

## What is it?
1. `array_sum.pyx`: Cython implementation of array element summation.
1. `compute_sums.py`: driver script to compare the implementations.
1. `setup.py`: build script.
1. `Makefile`: make file for building the cython extension and profiling
    the three implementations.
