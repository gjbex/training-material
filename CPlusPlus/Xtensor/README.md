# Xtensor

Illustration of how to use Xtensor, QuantStack numpy-like library for C++.


## What is it?

  1. `elementwise.cpp`: C++ application that illustrates creating a 2D array,
    initializing it elementwise, printing it to standard output,
    elementwise matrix expressions, elementwise application of user-defined
    functions using `xt::vectorize`, slicing and flattening.
  1. `svd.cpp`: C++ applicaton that reads a matrix from a CSV file,
    computes the singular value decomposition of it, reconstructs the
    matrix, and prints the differences between the reconstructed and
    original matrices.
  1. `matrix.csv`: CSV file with the element of a 2D floating point array.
  1. `Makefile`: make file to build the applicatons.
