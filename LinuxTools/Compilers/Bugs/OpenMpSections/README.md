# OpenMpSections
Interesting performance issue with Intel icc compiler (15.x, 16.x) when
using OpenMP sections.

## What is it?
* `false_sharing_intel_problem.c`: code that iterates over a shared array
    variable, updating values either in a pattern that could lead to false
    sharing, either in one that avoids it.  Parallelization is done through
    sections.
* `false_sharing_correct.c`: code that iterates over a shared array
    variable, updating values either in a pattern that could lead to false
    sharing, either in one that avoids it.  Parallelization is done through
    sections. The difference with the implementation above is that the loops
    have been encapsulated into a function.
* `Makefile`: make file to build 4 executables, two based on each source file,
    a version compiled with Intel icc, the other with GNU gcc.
* `false_sharing_correct_gcc.txt`: output for the correct implementation,
    gcc compiled.
* `false_sharing_correct_icc.txt`: output for the correct implementation,
    icc compiled.
* `false_sharing_intel_problem_gcc.txt`: output for the correct implementation,
    gcc compiled.
* `false_sharing_intel_problem_icc.txt`: output for the correct implementation,
    icc compiled.

## How to build?
Simply run `make`, the four versions of the executable will be compiled.

## Discussion
In each of the four cases, the correct result is computed.  However,
`false_sharing_intel_problem_icc.txt` shows a significant difference in
the time taken by each of the threads in the case where no false sharing
should occur.
