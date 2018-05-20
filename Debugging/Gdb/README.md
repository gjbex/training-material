# Gdb
Some examples to use while showing GDB features.

## What is it?
1. `array_bounds.c`: accesses an array out of bounds, no initialization
    of variable.
1. `array_bounds_f90.f90`: accesses an array out of bounds, also example
    of a "heisenbug" (works with GCC 5.4).
1. `crash.c`: segmentation fault due to double `free`.
1. `fib_main.c`: main program that uses incorrect Fibonacci
    implementation without a guard condition.
1. `fib.h`: declaration of the Fibonacci function.
1. `fib_not_okay.c`: implementation of the Fibonacci function without
    guard condition.
1. `fib_okay.c`: correct implementation of the Fibonacci function.
1. `hello_world.f90`: very simple OpenMP program to show thread
    switching in GDB.
1. `matrix.f90`: program exceeds 2D array bounds.
1. `matrix_mod.f90`: helper function for `matrix.f90`.
1. `fib_init.f90`: inappropriate local variable initialization makes
    variable static, leading to incorrect results.
1. `matrix_multiply.v90`: timings using `CPU_TIME` are off by an order
    of magnitude.
1. `Makefile`: make file to build the code.
