LoadBalancing
=============

Algorithm to balance the load of array processing between MPI processes,
the lower and upper bound are computed from the size and rank, and the
array length.

What is it?
-----------
1. `load_balancing.py`: Python prototype for the algorithm, for C and
    Fortran style indexing.
1. `load_balancing.c`: C MPI implementation.
1. `load_balancing.f90`: Fortran MPI implementation.
1. `Makefile`: make file to build C and Fortran MPI applications.
