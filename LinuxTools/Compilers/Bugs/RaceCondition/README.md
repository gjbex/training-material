# RaceCondition
Bug introduced by a macro that made sense in the old days, but that is
very problematic on modern CPUs.

## What is it?
* `spooky_macro.c`: very simple code that computes a sum of squares of
    double precision numbers.  the square is computed either as `x*x`,
    or using a macro taken from "Numerical Recipes", C version. Alternatively,
    another implementation of the macro leads to correct results.
* `Makefile`: make file will build four version of the program, two that use
    the bad macro, and two that use a better implementation, each compiled
    with Intel icc and GNU gcc.
* `make.txt`: output of the make command, showing that both icc and gcc
    generate warnings, but Intel only does so at the highest level of
    verbosity.    
* `Makefile.naive`: make file will build two version with icc, but with more
    naive compiler flags.
* `make_naive.txt`: output of the make command, showing that icc generates
    no warnings with naive compiler flags.
* `fail_gcc.txt`: output of version with suspicious macro compiled with gcc.
* `fail_icc.txt`: output of version with suspicious macro compiled with icc.
* `succeed_gcc.txt`: output of version with better macro compiled with gcc. 
* `succeed_icc.txt`: output of version with better macro compiled with icc. 

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

The following macro eliminates the problem, while keeping as close as
possible to the original, including the comparison to 0, which is of course
a very bad idea for multiple reasons.
```c
#define SQR(a) ((a) == 0.0 ? 0.0 : (a)*(a))
```
