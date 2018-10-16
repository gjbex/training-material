# FortranBlock
Experimental code to see whether using a Fortran block construct in an
OpenMP block works.

The OpenMP specification is silent on the subject. The Intel Fortran
compiler will yield an error (2018 version), while GCC's `gfortran`
will compile the code, and, at least for the examples, do the
intuitively right thing.

Obviously, this construction should not be used until the OpenMP
specification defines the semantics.

## What is it?
1. `block.f90`: simple Fortran application that gets and prints the
    thread number and number of threads for each thread in a parallel
    region.
1. `Makefile`: make file to build the applications.
