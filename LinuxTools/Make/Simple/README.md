Simple
======

Basic Makefile for multiple targets, illustrating patterns and special
variables.

Contents
--------
1. `x.f90`: main Fortran program that must be build using  the
    module `a_mod.f90`.
1. `y.f90`: main Fortran program that must be build using  the
    module `b_mod.f90`.
1. `a_mod.f90`: module to build `x.f90` with.
1. `b_mod.f90`: module to build `y.f90` with.
1. `Makefile`: builds the two targets.
