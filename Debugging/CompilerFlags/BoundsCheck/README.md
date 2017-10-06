# BoundsCheck
The Fortran compiler allows to enable run time array bounds checking.

## What is it?
1. `array_bounds_check.f90`: simple program that accesses data beyond
    the array bounds.
1. `bounds_check_impact.f90`: application that performs many array
    accesses to estimate performance impact of bounds check.
1. `Makefile`: make file to build the application, and generate warnings
    with appropriate compiler flag.

## How to use?
To build:
```bash
$ make
```

To show warnings:
```bash
$ make warnings
```
Note: make will report that the recipe for target 'warnings' failed, which
is to be expected since the application aborts when the array bounds check
notices a problem.

To do timings for performance impact:
```bash
$ make timings
```
