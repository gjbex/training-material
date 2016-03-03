# Exceptions
Error handling in Cython code.

## What is it?
1. `average.pyx`: code to be compiled using Cython, implements two
    functions to compute the average of an array slice, one with, the
    other without error handling.
1. `setup.py`: Python build script.
1. `Makefile`: make file to build the extension.
1. `compute_average.py`: script to load the compiled module and call the
    implemented function with and without error handling.
