Fortran matrices
================

A nice feature of Fortran is that matrices are first class citizens,
i.e., compilers can actually exploit this for optimization, vectorization,
and even parallelization.

What is it?
-----------
1. `calculations`: illustrates mathematical operations with matrices such
   as addition, element-wise multiplication, division and exponentiation,
   as well as matrix product.
2. `alloc_test`: illustrates how to dynamically allocate a matrix with
   dimensions that can be specified on the command line.  The matrix is
   allocated, initialized, printed, and deallocated.

Note: both programs use the `matrix_ops` module in `matrix_ops.f90` that
defines two subroutines, `init_matrix` to initialize a matrix, and
`print_matrix` to write it to the screen.  Both illustrate how to pass
a matrix of arbitrary dimensions to a procedure, and determine those
using the `shape` function.
`print_matrix` also illustrates how to dynamically create a format string.

How to build?
-------------
A make file is provided.

