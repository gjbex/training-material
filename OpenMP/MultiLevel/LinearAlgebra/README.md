# MultiLevel

Thread-parallelism can be done at multiple levels.  By way of example, we
consider the LAPACK SVD as implemented in Intel's MKL.

## What is it?

1. `matrix_mod.f90`: module containing various subroutines to read a matrix
   from an HDF5 file, compute its singular value decomposition, recompute the
   original matrix, and compute relative differences.
1. `utils_mod.f90`: module containing subroutines to handle command line
   arguments.
1. `svd.f90`: main program that computes the SVD decomposition of a matrix
   in an HDF5 file, and writes out the relative difference between the
   original and the recomputed matrix.
1. `multi_svd.f90`: main program that computes the SVD decomposition of a
   matrix in an HDF5 file, and writes out the relative difference between the
   original and the recomputed matrix.
1. `Makefile`: make file for GCC gfortran compiler, OpenBLAS and Lapack,
   This should work on desktop Linux systems (tested with Ubuntu 19.04).
1. `Makefile.intel`: make file to the Intel ifort compiler, and MKL's
   BLAS and Lapack implementations.  This version can be used to explore
   multi-level parallelism.
1. `Makefile.foss`: make file to the GCC gfortran compiler, and OpenBLAS
   Lapack implementations.  This version can be used to explore
   multi-level parallelism.
1. `serial.pbs`: job script to run the sequential application with
   sequential MKL.   
1. `threaded.pbs`: job script to run the sequential application with
   OpenMP MKL.   
1. `multi_serial.pbs`: job script to run the OpenMP application with
   sequential MKL.   
1. `multi_threaded.pbs`: job script to run the OpenMP application with
   OpenMP MKL.   
1. `small_test_*.h5`: sample input HDF5 files containing a 3 by 4
   double precision matrix.
1. `performance.xlsx`: Performance numbers for various configurations
   on four 10,000 by 10,000 double precision matrices.
