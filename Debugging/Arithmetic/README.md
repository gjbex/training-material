# Arithmetic
Some illustrations of arithmetic bugs.

## What is this?
1. `addition.py`: illustration of loss of precision when adding numbers
    of different orders of magnitude.
1. `addition.c`: C implementation of illustration of loss of precision
    when adding numbers of different orders of magnitude.
1. `float_overflow.c`: illustration of code that generates `inf`.
1. `float_overflow_nan.c`: illustrates overflow and not-a-number resulting
    from various computations.
1. `equality.c`: illustrates that testing for floating point equality is
    a bad idea.
1. `overflow.cpp`: illustration of integer arithmetic overflow when using a
    counter. The application reads a DNA sequence from standard input,
    and counts the number of A, C, G, T nucleotides.
1. `dna_generator.py`: Script to generate a DNA sequence of specified
    composition, used to generate input for `overflow.cpp`.
1. `trace_nan.f90`: code to illustrate how to trace the origin of a NaN
    by enabling compiler FPE trapping.
1. `underflow.c`: illustration of numerical underflow in floating point
    artihmetic.
1. `Makefile`: make file to build the applications.
