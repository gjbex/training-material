# Fortran functions

A number of features of Fortran procedures are illustrated.  Procedures
can be passed to other procedures as arguments, where type information is
provided via an interface.  Functions can be defined recursively.

## What is it?
-
1. `recursion_test`: the `funcs_mod` module defines the recursive function
    `factorial` that compute `n!` recursively.
1. `time_funcs`: the program times a number of mathematical functions
    defined in `math_functions_mod.f90`.  All functions defined in that
    module satisfy the interface defined in the module 
    `math_func_interface` so that they can be passed as arguments to
    the subroutines in `time_func_mod.f90` that perform the actual timing.
1. `internals_test`: illustrate how to use internal procedures, and
    scoping rules.
1. `elemental_test`: implementation of the factorial function so that it
    it can be applied to arrays
1. `compute_stats_test`: compute descriptive statistics (mean, standard
    deviation) in a subroutine to illistrate intent declarations.
1. `intrinsic_test`: illustrates that many intrinsic procedures are
    elemental.
1. `initialization_test`: illustrates that procedure local variables
    retain their value between procedure calls when initialized in
    declaration.
1. `quad_test`: illustrates using a function as a procedure argument
1. `quick_sort`: illustration of a recursive subroutine.
1. `line_test`: extra, more sensible example of internal procedures
1. `root.f90`: compute root of a function using bisection method,
    illustrates use of an interface.

## How to build?

A make file is provided.
