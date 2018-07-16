# ConstQual
In C/C++ it is possible to inadvertedly modify the value of a constant
by a type cast to a non-const pointer.

## What is it?
1. `const_qual.c`: C application that modifies a `const int`.
1. `Makefile`: make file to build the application, and generate warnings
    with appropriate compiler flag.

## How to use?
To build:
```bash
$ make
```

To show warnings:
```bash
$ make warnings
```
