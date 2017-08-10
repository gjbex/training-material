# JuliaSet
Compute the Julia set to illustrate the use of OpenMP in Cython.

## What is it?
1. `julia_set.py`: driver program used to run the various implementations,
    selectable by command line option.
1. `julia_python.py`: Python implementation of Julia set computation.
1. `julia_cython.pyx`: Cython implementation of Julia set computation.
1. `julia_cython_omp.pyx`: Cython implementation of Julia set computation
    that uses OpenMP for multithreading.
1. `setuo.py`: build script for the Cython extension.
1. `Makefile`: make file for the Cython extension
