# SvD
Illustration of computing the singular value decomposition of a matrix.
Note that the way to reconstruct the original matrix from U, S, and VT
is definitely not efficient, however, constructing the Sigma matrix
consumes some more memory, which is the purpose of the application.

## Contents
1. `create_h5.f90`: creates an HDF5 file containing a matrix with elements
    drawn from a uniform random distribution.
1. `create_test_h5.f90`: creates an HDF5 file containing a matrix with
    row-wise increasing number starting from 1.0.  This matrix is useful
    for debugging distributed reads of the HDF5 file.
1. `dump_h5.f90`: writes a matrix contained in an HDF5 file to standard
    output.
1. `svd.f90`; computes the SVD of a matrix read from an HDF5 file using
    `dgesvd`, reconstructs the matrix using `dgemm`, and computes the
    relative error.
1. `svd_blacs.f90`: compute the SVD of a maatrix read from an HDF5 file
    using Scalapack's `pdgesvd`, reconstructs the matrix using PBLAS's
    `pdgemm` and computes the relative error.
1. `matrix_mod.f90`: a few common subroutines for reading and writing
    matrices.
1. `utils_Mod.f90`: a few common subroutines to retrieve command line
    arguments.
1. `Makefile`: make file to build the code.
1. `build.sh`: Bash script to drive the make process when building with
    Intel's MKL library (11.2).
1. `setenv.sh`: file to be sourced, setting up the enivronment to run
    the executables with Intel's MKL.
