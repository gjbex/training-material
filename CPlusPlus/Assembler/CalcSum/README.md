# CalcSum

Implementations of assembly functions to compute the sum of three integer
arguments, returning that sum.  The assembly functions can be used from
C/C++ code.

## What is it?

  1. `calc_sum_function_compiler.nsm`: assembly implementation of the
    function inspired by reverse engineering the output of a compiler.
  1. `calc_sum_function.nsm`: assembly implementation that is 7 % faster.
  1. `calc.cpp`: C++ program that uses the assembly function.
  1. `timing.cpp`: C++ program that times the assembly function.
  1. `Makefile`: make file to build the applications.

## How to use it?

Three applications will be build:

  * `calc_sum.exe`: takes three command line arguments and computes the
    sum using the assembly function.
  * `timing.exe`: times the faster assembly function, optionally takes a
    command line argument to control the runtime (default: 2000, scales
    with a power of 3).
  * `timing_compiler.exe`: times the assembly function inspired by the
    compiler, optionally takes a command line argument to control the
    runtime (default: 2000, scales with a power of 3).
