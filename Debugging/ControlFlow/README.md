# ControlFlow
These code samples represent a collection of control flow related bugs.

## What is it?
1. `bitwise_vs_logical.c`: illustration of results of using a bitwise
    operator where a logical operator should be used.
1. `count_nucleotides.c`: illustrates a problem with `while` loop
   termination.
1. `seq.fasta`: input file (FASTA-like) for `count_nucleotides_c.exe`.
1. `logical_control_flow.c`: illustration of using semantics of
    logical evaluation for control flow (not idiomatic!).
1. `logical_order.f90`: order of evaluation of logical expressions in
    Fortran is not guaranteed, which may be problematic when using
    procedures with optional arguments.  This code doesn't seem to crash,
    so the compilers coincidentally do the right thing.
1. `logical_order.c`: evaluation of Boolean expressions in C/C++ is lazy,
    so evaluation order is fixed, and has to be taken into account. This
    code will terminate with a segmentation fault. valgrind will catch
    this.
1. `improper_conditionals.c`: "unexpected" behaviour due to improper
    Boolean expressions in conditional statement.
1. `run_improper_conditionals.sh`: Bash script to run the improper
    conditionals example program, and produce the "unexpected" output.
    Boolean expressions in conditional statement.
1. `init_proc_vars.f90`: illustrates potential bug when initializing
    variables in Fortran procedures.
1. `udt_intent_out.f90`: illustration of bug caused by inappropriate use
    of intent `OUT` when partially assigning to a variable of a user
    defined type.
1. `unintended_global.f90`: illustration of a bug introduced by omitting
    a local variable declaration in a function (infinite loop).
1. `Makefile`: make file to build the applications.
