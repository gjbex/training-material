# FloatEqual
Comparing two floating point values wuing the equality or inequality
operator typically makes no sense at all due to round off.  Compilers
can emit relevant warnings.

## What is it?
1. `float_equal.c`: simple C program that checks whether the square
    of the square root of 2 is equal to 2.
1. `float_equal.f90` simple Fortran program that checks whether the square
    of the square root of 2 is equal to 2.
1. `on_circle.c`: application to test whether a 2D point lies on a circle.
1. `Makefile`: make file to build the application, and generate warnings
    with appropriate compiler flag.
1. `on_circle_driver.py`: driver for the `on_circle` application.

## How to use?
To build:
```bash
$ make
```

To show warnings:
```bash
$ make warnings
```
