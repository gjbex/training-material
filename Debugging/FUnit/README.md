# FUnit
Illustration of a few simple unit tests using the fUnit framework for
Fortran.

## What is it?
1. `fac_mod.f90`: Fortran module implementing the function to compute
    the number of permutations.
1. `fac_mod.fun`: unit tests for the `fac_mod` module, the last of which
    is designed to fail.
1. `Makefile`: make file to execute the tests, and clean up afterwards.
    Note that using the `-fno-range-check` is a very bad idea, it is done
    here to ensure that the compiler doesn't catch the mistake that makes
    the last test fail.

Note: fUnit tests should not be indented, i.e., `test ...` and the
corresponding `end` should start in the first column of the file.

## How to use?
Simple execute `make`:
```bash
$ make
```
