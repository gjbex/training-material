# Cython
Testing Cython code using the `pytest` framework.

## What is it?
1. `fac.py`: Python script to compute the factorial function for a range
    of values.
1. `fac_cython.pyx`: Cython implementation of the factorial function.
1. `test_fac.py`: implementation of tests for `pytest`.
1. `setup.py`: Python build script.
1. `Makefile`: make file to build the extension.

## How to use?
To build the Cython extension:
```bash
$ make
```

To run the tests:
```bash
$ make test
```
