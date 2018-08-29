# IntegerOverflow
Illustration of how to use a compiler flag to trap integer overflow.

## What is it?
1. `fac.c`: application that computes the factorial of a number.
1. `Makefile`: make file to build the applications.

## How to use?
Build the applications using the make file.  Two versions will be
built, one (`fac.exe`) without trapping integer overflow, while the
other (`fac_trapped.exe`) traps the overflow.

Run with, e.g., argument 30 to observe the difference.
