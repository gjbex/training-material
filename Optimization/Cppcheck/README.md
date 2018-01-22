# Cppcheck
Some illustrations of performance issues detected by `cppcheck`.

## What is it?
1. `list_stl_orig.cpp`: very basic illustration of using STL lists, with
    performance warnings by `cppcheck`.
1. `list_stl_fixed.cpp`: very basic illustration of using STL lists, with
    performance warnings by `cppcheck` fixed.
1. `priority_queue.cpp`: implements an example of using a priority queue
    for non-trivial items with peformance warnings by `cppcheck`.
1. `priority_queue.cpp`: implements an example of using a priority queue
    for non-trivial items with peformance warnings by `cppcheck` fixed.
1. `Makefile`: make file to build the sample code.

## How to use?
To run `cppcheck` do
```bash
$ make check
```
