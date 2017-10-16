# Branching
Branching instructions (`if` statements) may hinder vectorization.

## What is it?
1. `branch.c`: C application that times two functionally equivalent
    loops, one with an `if` statement, the other with a cnoditional
    expression.
1. `Makefile`: make file to build the application.
