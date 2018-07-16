# OpenMP
Illustration of some bugs typical for OpenMP, as well as code to
demonstrate features of debuggers for handling multi-threaded code.

## What is it?
1. `010.pi.f90`: Fortran code that computes pi by throwing darts.
1. `020.pi.f90`: Fortran code that computes pi by throwing darts, with
    OpenMP barrier added to simplify comparing thread results.
1. `Makefile`: make file to build the code.
