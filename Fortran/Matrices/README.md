Fortran matrices
================

A nice feature of Fortran is that matrices are first class citizens,
i.e., compilers can actually exploit this for optimization, vectorization,
and even parallelization.

What is it?
-----------
1. `calc_test.f90`: illustrates mathematical operations with matrices such
    as addition, element-wise multiplication, division and exponentiation,
    as well as matrix product.  Adding a scalar to or multiplying a scalar
    with all elements of a matrix can also be done in a single statement.
1. `matrix_ops.f90`: module defining some procedure on matrices
1. `calc_alloc_test.f90`: illustrates that procedures need not be aware
    that they work with allcated arrays.
1. `alloc_test.f90`: illustrates how to dynamically allocate a matrix with
    dimensions that can be specified on the command line.  The matrix is
    allocated, initialized, printed, and deallocated.
1. `pointer_test.f90`: illustrates that procedures need not be aware
    that they work with a pointer to arrays, rather than the real thing.

Note: both programs use the `matrix_ops` module in `matrix_ops.f90` that
defines two subroutines, `init_matrix` to initialize a matrix, and
`print_matrix` to write it to the screen.  Both illustrate how to pass
a matrix of arbitrary dimensions to a procedure, and determine those
using the `shape` function.
`print_matrix` also illustrates how to dynamically create a format string.

How to build?
-------------
A make file is provided.
