# Assertions
Some illustrations of using assertions for checking preconditions,
postconditions and invariants.

Note that assertions should be disabled in production code by
defining `NDEBUG`, and hence can not be used for error handling.

## What is it?
1. `assertions.c`: C application that computes the factorial of a
    given number, using assertions to check preconditions and
    invariants.
1. `Makefile`: make file to build the applications.
1. `Makefile.prod`: make file to illustrate how to build for
    debugging as well as production.

## How to use it?
When building the software, two applications will be built.  They are
identical, except that one has assertions enabled (`assertions.exe`),
while for the other (`assertions_no_asserts.exe`) they are disabled.

Run with arguments such as -2 and 30 to see the difference.

To illustrate the alternative make file, it can be used as:
```bash
$ make debug
```
This will create an executable with assertions enabled.

```bash
$ make release
```
This will create an executable with assertions disabled.
