# ImplicitNone
In Fortran, it is important to declare variables explicitely, since by
default, implicit typing is enabled.  All variables starting with the
characters `i` to `p` are implicitely `integer`, while all others are
implicitely `real`.

## What is it?
1. `implicit_not_none.f90`: application produces unexpected results,
    printing `integer` values rather than `real`, which are quite
    incorrect.
1. `implicit_none.f90`: application produces the expected results.
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
