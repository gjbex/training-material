# C libraries for R

Illustration of wrapping a C function for use in R.


## What is it?

1. `myRLib.c`: implementation of a C function.
1. `Makefile`: make file to build the shared library.
1. `myRLib.R`: R wrapper function around the C function call.
1. `my_script.R`: R script that uses the wrapper function.
