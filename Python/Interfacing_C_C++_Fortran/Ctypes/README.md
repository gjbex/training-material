# Ctypes

The ctypes Python standard library module is convenient
to wrap simple shared library functions.

## What is it?

1. `logistic_map.h`: declaration of the logistic map function.
1. `logistic_map.c`: implementation of the logistic map function.
1. `Makefile`: make file to build the shared library containing
    the logistic map function.
1. `log_map_cdll.py`: Python script that loads and calls the
    logistic map function in the shared library.
