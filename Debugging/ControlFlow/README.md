# ControlFlow
These code samples represent a collections of control flow related bugs.

## What is it?
1. `logical_order.f90`: order of evaluation of logical expressions in
    Fortran is not guaranteed, which may be problematic when using
    procedures with optional arguments.  This code doesn't seem to crash,
    so the compilers coincidentally do the right thing.
1. `logical_order.c`: evaluation of boolean expressions in C/C++ is lazy,
    so evaluation order is fixed, and has to be taken into account. This
    code will terminate with a segmentation fault. valgrind will catch
    this.
1. `Makefile`: make file to build the applications.
