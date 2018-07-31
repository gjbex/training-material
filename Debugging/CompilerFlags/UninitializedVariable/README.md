# UninitializedVariable
Illustration of a bug introduced by an uninitialized stack variable.

## What is it?
1. `uninitialized_variable.c`: C version of the code.
1. `uninitialized_variable.f90 Fortran version of the code.
1. `Makefile`: make file to build the applications.
1. `Makefile.intel`: make file to build the applications using the
    Intel compilers.

## How to use?
To create the applications with bugs without warnings:
```bash
$ make
```
To run:
```bash
$ ./uninitialized_variable_c.exe
$ ./uninitialized_variable_f90exe
```

To view warnings when running with compiler warnings enabled:
```bash
$ make warnings
```

To build with intel:
```bash
$ make -f Makefile.intel
```
