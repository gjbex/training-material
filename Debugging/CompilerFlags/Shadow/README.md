# Shadow
Illustrates how to use the `-Wshadow` compiler option to detect
potential problems caused by local variable decleration that shadow
outer scope variables.

## What is it?
1. `shadow.c`: C implementation of an application that should print
    whether numbers up to some value are prime.
1. `Makefile`: make file to build applications and generate warnings

## How to use?
To build a correct and a buggy version of the application:
```bash
$ make
```

The buggy version will not print anything:
```bash
$ ./shadow_bug.exe
```
The version without the bug produces the expected output.
```bash
$ ./shadow_okay.exe
```

To view the warnings generated when using the `-Wshadow` options, run:
```bash
$ make warnings
```
