# Gdb
Some examples to use while showing GDB features.

## What is it?
1. `array_bounds.c`: accesses an array out of bounds, no initialization
    of variable.
1. `show.h`: helper function declaration for `array_bounds.c`.
1. `show.c`: helper function for `array_bounds.c`.
1. `crash.c`: segmentation fault due to double `free`.
1. `fib.c`: recursive Fibonacci number implementation for demonstrating
    missing command line argument problem, and deep stack.
1. `hello_world.f90`: very simple OpenMP program to show thread
    switching in GDB.
1. `matrix.f90`: program exceeds 2D array bounds.
1. `matrix_mod.f90`: helper function for `matrix.f90`.
1. `fib_init.f900`: inappropriate local variable initialization makes
    variable static, leading to incorrect results.
1. `Makefile`: make file to build the code.
