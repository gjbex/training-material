# BadFunctionCast
In C/C++ casting the return value of a function can lead to errors if not
carefully checked.

## What is it?
1. `bad_function_call.c`: C application that performs a cast on the
    return value of a function, causing an overflow.
1. `error_handling.c`: illustration of doing error handling when using
    `lround`.
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
