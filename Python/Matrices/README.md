Mattrices
=========

These implementations of the matrix-matrix multiplications in various
languages are intended to illustrate some bad practices and their
performance impact.

What is it?
-----------
1. `pure_python_matmul.py`: matrix multiplication based on a representation
   as list of lists, very slow, do not ever do this
2. `numpy_matmul.py`: numpy.dot function used to multiply numpy matrices,
   performance depends on quality of underlying BLAS library, but at any
   rate orders of magnitude faster than naive implementation
3. `pure_fortran_matmul.f90`: Fortran implementation using the matmul
   initrinsic function
4. `blas_fortran.f90`: Fortran implementation using the DGEMM BLAS level 3
   procedure
5. `pure_c_matmul.c`: naive C implementation

A make file is provided to build the Fortran and C implementations.

