# DanglingPointers
The Intel compilers `icc`/`icpc` have some useful flags to check for pointer
issues at runtime.

## What is it?
1. `dangling.c`: C code that uses a dangling pointer.
1. `Makefile`: make file to build the code.
1. `Makefile.intel`: make file to build the code using the
    Intel compiler.

## How to use?
To build without specific pointer checks:
```bash
$ make
```

To build with pointer checks:
```bash
$ make debug
```

To build using the Intel compilers:
```bash
$ make -f Makefile.intel
```
