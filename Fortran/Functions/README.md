Fortran functions
=================

A number of features of Fortran procedures are illustrated.  Procedures
can be passed to other procedures as arguments, where type information is
provided via an interface.  Functions can be defined recursively.

What is it?
-----------
1. `recursion`: the `funcs_mod` module defines the recursive function
   `factorial` that compute `n!` recursively.
2. `time_funcs`: the program times a number of mathematical functions
   defined in `math_functions_mod.f90`.  All functions defined in that
   module satisfy the interface defined in the module 
   `math_func_interface` so that they can be passed as arguments to
   the subroutines in `time_func_mod.f90` that perform the actual timing.

How to build?
-------------
A make file is provided.

