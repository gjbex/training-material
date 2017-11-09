# UnspecifiedOrder
Bug introduced by a macro that made sense in the old days, but that is
very problematic on modern CPUs.

## What is it?
* `spooky_macro.c`: very simple code that computes a sum of squares of
    double precision numbers.  the square is computed either as `x*x`,
    or using a macro taken from "Numerical Recipes", C version. Alternatively,
    another implementation of the macro leads to correct results.
* `Makefile`: make file to show (the absense of) warming genrated by
    Intel icc and GNU gcc, and build the executables.
* `warnings.txt`: output of the `make warnings` command, showing that
    both icc and gcc generate warnings, but Intel only does so at the
    highest level of
    verbosity.    
* `warnings.txt`: output of the `make warnings` command, showing that icc
    generates no warnings with naive compiler flags.
* `gcc.txt`: output of version compiled with gcc.
* `x_icc.txt`: output of version compiled with icc.

## Discussion
This example is a good illustration that it is wise to have as many compiler
warnings switched on as possible.  It also illustrates a bug in the Intel
compiler that, when using the following macro, incorrect code is generated.
```c
static double __arg__;
#define SQR(a) ((__arg__ = (a)) == 0.0 ? 0.0 : __arg__*__arg__)
```
The use of the static global variable `__arg__` in this macro leads to a
race condition that produces incorrect results. No one questions that this
implementation if badly flawed, but a compiler should try to detect this,
and produce correct code. GNU gcc and clang do, Intel icc does not.

Using `make warnings` also illustrates that `-Wfloat-equal` for gcc may
also report potential problems.

## Compiler versions
* Intel icc: 13.x-17.x
* GNU gcc: 4.9.x-7.0
