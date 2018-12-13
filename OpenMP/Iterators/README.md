# Iterators

Using C++ iterators in OpenMP for-loops.  The code also illustrates the
use of the new `linear` clause on for loops.

## What is it?

  1. `vector.cpp`: simple application to experiment with iterating
    over a C++ `std::vector` using `[]` and a random access iterator.
    The schedule can be set at runtime.
  1. `Makefile`: make file to build the applications.

## How to use?

Tow applications can be build, one using a for loop over the vector
index, the other (when `ITERATOR` is defined at compile time over
a random access iterator.  The applications take the vector length as
optional command line argument.  Using `OMP_SCHEDULE`, it is possible
to experiment with various schedules at runtime.
