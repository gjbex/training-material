Allocation
==========

Illustrates how to initialize an array in parallel, and ensure that the
processing is also done in parallel, so that the threads operate on the
part of the array they initialized in another parallel region.

What is it?
-----------
1. `allocation.c`: C program to illustrate thread allocation and
    processing in separate parallel regions.
1. `Makefile`: make file for GCC.
1. `Makefile.intel`: make file for Intel.
