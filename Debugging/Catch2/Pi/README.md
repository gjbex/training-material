# Pi
Simple example of using Catch2 for C++ unit testing.  Illustrates testing
for floating point numerical comparisons.

## What is it?
1. `pi.cpp`: implementation of a function that computes computes a
    quadrature to compute pi.
1. `pi.h`: declaration of the pi function.
1. `test_pi.cpp`: Catch2 tests for the pi function, illustrating how to
    check approximate floating point equality. Note that the last
    requirement fails on purpose.
1. `test_main.cpp`: main function to drive the tests.
1. `Makefile`: make file to build the test appliation.

## How to use?
Building and running the tests:
```bash
$ make checks
```
