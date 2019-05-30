# Mkl

Illustration of how to build a C++ application that uses the Eigen
template library for linear algebra to use Intel MKL under the hood.

## What is it?

1. `matrix_product.cpp`: application that uses Eigen to represent
    matrices, ad compute their product.
1. `Makefile`: make file to build the application using Intel's MKL.
1. `matrix_product.pbs`: PBS script to run and benchmark the
    application.
