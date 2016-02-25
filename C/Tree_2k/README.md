# `tree_2k`
This is a library that implements a tree data structure to store and
query spatial data.

It is similar to a quadtree, but works for any specified rank.

## What is it?
1. `benchmarks`: a few benchmarks to compare a naive algorithm with
    `tree_2k` on performance and memory overhead.
1. `examples`: programs that use the `tree_2k` library.
1. `src`: contains the source code of the implementation of the data
    structures and algorithms.
1. `src/test`: unit tests written for the `CUnit` framework.
1. `tree_2k.pptx`: Powerpoint presention on `tree_2k`.
    

## Requirements
* A C99 compliant compiler, and GNU make to build.
* To compile and run the tests, CUnit is required.
* To generate HTML and LaTeX documentation, doxygen is required.
