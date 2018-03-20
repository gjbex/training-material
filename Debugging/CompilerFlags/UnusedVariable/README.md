# UnusedVariable
Although unused variables are not really a bug, but may lead to
confusion.

## What is it?
1. `unused_var.c`: C application that contians a bug due to confusion
    about a global variable (evil!).
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

Making with appropriate variable definition:
```bash
$ make correct
```
