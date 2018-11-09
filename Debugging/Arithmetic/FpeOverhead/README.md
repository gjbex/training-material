Integrate
=========

This illustrates the implementation by two user defined types of and
abstract type that declares an abstract procedure.

What is it?
-----------
1. `quad_func_interface.f90`: definition of an interface for functions
    that one can compute the quadrature for.
1. `quad_mod.f90`: abstract user defined type that quadrature
    implementations should extend, it defines an abstract interface for
    the integrate procedure.
1. `gauss_mod.f90`: implementation of the `quad_type`, Gauss-Legendre
    quadrature (10 points), and a general method for any number of points.
1. `gauss_test.f90`: computes quadrature using general Gauss-Legendre
    method.
1. `Makefile`
1. `build.sh`: Bash script to build a version with FPE traps, and one
    without for timing purposes.
1. `run.sh`: Bash script to run and time the version with and without FPE
    trapping.
