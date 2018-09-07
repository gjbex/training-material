# Conversions
Illustration of using compiler flags to warn about suspicous data
conversions.

## What is it?
1. `conversions.c`: illustration of narrowing type conversions in C.
1. `conversions.f90`: illustration of narrowing type conversions in
    Fortran.
1. `Makefile`: make file to build the applications.

## How to ue it?
Do do a default build, simply use
```bash
$ make
```
This will not issue any warnings.

To compile with `-Wconversion`, use
```bash
$ make warnings
```
