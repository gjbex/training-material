SVD
===

Illustration of computing the singular value decomposition of a matrix.

Contents
--------
1. `create_h5.f90`: creates an HDF5 file containing a matrix with elements
    drawn from a uniform random distribution.
1. `dump_h5.f90`: writes a matrix contained in an HDF5 file to standard
    output.
1. `svd.f90`; computes the SVD of a matrix read from an HDF5 file using
    `dgesvd`, reconstructs the matrix using `dgemm`, and computes the
    relative error.
1. `matrix_mod.f90`: a few common subroutines for reading and writing
    matrices.
1. `utils_Mod.f90`: a few common subroutines to retrieve command line
    arguments.
1. `Makefile`: make file to build the code.
1. `build.sh`: Bash script to drive the make process when building with
    Intel's MKL library (11.2).
1. `setenv.sh`: file to be sourced, setting up the enivronment to run
    the executables with Intel's MKL.
