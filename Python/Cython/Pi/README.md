# Pi
Compute pi using the quadrature of `sqrt(1 - x**2)` on `[-1.0, 1.0]`,
using Cython's OpenMP support.  This illustrates that Cython automatically
infers the variables to use in a reduction.

## What is it?
1. `pi_lib.pyx`: implementation of the quadrature using OpenMP.
1. `pi.py`: script to compute pi.
1. `setuo.py`: build script for the Cython extension.
1. `Makefile`: make file for the Cython extension
