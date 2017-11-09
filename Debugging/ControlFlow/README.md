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
1. `improper_conditionals.c`: "unexpected" behavior due to improper
    boolean expressions in conditional statment.
1. `run_improper_conditionals.sh`: Bash script to run the improper
    conditionals example program, and produce the "unexpected" output.
    boolean expressions in conditional statment.
1. `init_proc_vars.f90`: illustrates potential bug when initializing
    variables in Fortran procedures.
1. `unintended_global.f90`: illustration of a bug introduced by omitting
    a local variable declaration in a function (infinite loop).
1. `Makefile`: make file to build the applications.
