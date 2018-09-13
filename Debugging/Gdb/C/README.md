# C
Some C examples to use while showing GDB features.

## What is it?
1. `array_bounds.c`: accesses an array out of bounds, no initialization
    of variable (works with GCC 5.4).
1. `crash.c`: segmentation fault due to double `free`.
1. `fib_main.c`: main program that uses incorrect Fibonacci
    implementation without a guard condition.
1. `fib.h`: declaration of the Fibonacci function.
1. `fib_not_okay.c`: implementation of the Fibonacci function without
    guard condition.
1. `fib_okay.c`: correct implementation of the Fibonacci function.
1. `hello_world.c`: very simple OpenMP program to illustrate thread
    switching.
1. `Makefile`: make file to build the code.
1. `Scenarios`: scenarios for illustrating GDB features.
1. `Features`: applications to illustrate GDB features.
