# QuadCalc

Illustration of double precision function called from C++.  The function to
compute is `(3.14*x - 2.4) + 1.9`

## What is it?

  1. `quad.nsm`: assembly implementation of the function.
  1. `quad_calc.cpp`: C++ application that calls the assembly implementation.
  1. `timing.cpp`: C++ application that times the assembly function, as
    well as a C++ inline version and verifies the respective results.
  1. `quad_calc_inline.cpp`: C++ application that calls an inline C++
    function.  Intended for disassembling to illustrate what a smart
    compiler can do.
  1. `Makefile`: make file to build the applications.

## How to use it?

The make file builds three applciations:

  * `quad_calc.exe`: takes a floating point command line argument, and
    prints the result computed by the assembly function to standard output.
  * `timing.exe`: takes an optional integer argument that controls the run
    time (default: 1000000000, scales linearly).  it prints the time
    it takes to evaluate the function that many times, both for the C++
    inline version and the assembly version.  It also prints the difference
    between the sums of all the values computed by the respective functions.
  * `quad_calc_inline.exe`: takes a floating point command line argument, and
    prints the result computed by the C++ inline function to standard output.
    This is mainly intended for disassembly.

To disassemble:

```bash
$ objdump -Mintel -d timing.exe
```
