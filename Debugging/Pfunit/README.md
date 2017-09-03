# Pfunit
Illustration of a few simple unit tests using the pFUnit framework for
Fortran.

## What is it?
1. `fac_mod.f90`: Fortran module implementing the function to compute
    the number of permutations.
1. `fac_tests.fp`: unit tests for the `fac_mod` module, the last of which
    is designed to fail.
1. `testsSuites.inc`: test suites definition file.
1. `Makefile`: make file to execute the tests, and clean up afterwards.

## How to use?
Simple execute `make`:
```bash
$ make
```
