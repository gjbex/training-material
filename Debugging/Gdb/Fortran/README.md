# Fortran
Some Fortran examples to use while showing GDB features.

## What is it?
1. `array_bounds.f90`: accesses an array out of bounds, also example
    of a "heisenbug" (works with GCC 5.4).
1. `fib.f90`: recursive implementation of the Fibonacci function that
    goes into infinite recursion.
1. `hello_world.f90`: very simple OpenMP program to show thread
    switching in GDB.
1. `fac_init.f90`: inappropriate local variable initialization makes
    variable static, leading to incorrect results.
1.  `fac_mod.f90`: (incorrect) implementation of the factorial function.
1. `matrix.f90`: program exceeds 2D array bounds.
1. `matrix_mod.f90`: helper function for `matrix.f90`.
1. `matrix_multiply.v90`: timings using `CPU_TIME` are off by an order
    of magnitude.
1. `Makefile`: make file to build the code.
1. `Features`: applications specifically written to illustrates GDB
    features.
    Fortran programs that use non-trivial user defined types, pointers
    and recursion.
1. `Scenarios`: scenarios for illustrating GDB features.
