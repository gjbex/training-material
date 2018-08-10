# NullPointer
Code to illustrate detection of NULL pointer dereferencing by GCC's
sanitizer.

## What is it?
1. `null_pointer.c`: C program that will dereference a NULL pointer
    (unless you've more than a TB of RAM).
1. `Makefile`: make file to build the application.    `

# How to use?
To build without instrumentation:
```bash
$ make segfault
```
with instrumentation:
```bash
$ make error_msg
```
