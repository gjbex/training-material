# PETSc
A few illustrations of using the PETSc library (Portable, Extensible
Toolkit for Scientific Computation).

Note that using PETSc effectively requires more than a passing
nderstanding of the non-trivial mathematics involved.  These code samples
are merely technical in nature.

## What is it?
1. `vec_norm.c`: computing the vector 1-norm of a distributed vector.
1. `vec_assembly.c`: setting the values of a distributed value locally.
1. `solve_dense.c`: illustrates solving a system of linear equations
    with a dense matrix as operator.
1. `Makefile`: make file to build the applications.
