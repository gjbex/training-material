# SyntaxSemantics
This is a small collection of trivial programs to illustrate syntax errors
versus semantic errors.

## What is it?
1. `syntax_error.f90`: hello-wporld program with a syntax error.
1. `semantic_error.f90`: buggy implementation of the factorial function to
    illustrate a semantic error.
1. `Makefile`: make file to build the applications, or illustrate the
    errors caught by the compiler.

## How to use it?
To build the applications with semantic errors, simply run `make`.

To compile the code with syntax explicitly specify the targets:
```
$ make syntax_error_f90.o
```
