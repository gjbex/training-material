# UndefMacroVar
When using preprocessor macro variables, unexpected things may happen when
such a a variable is undefined, and used in an `#if` macro.

## What is it?
1. `undef_macro_var.c`: C application that compiles using `float` or
    `double` depending on the value of a macro variable `PREC`.
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
