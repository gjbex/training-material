# CodeCoverage
Illustration of how to use code coverage tools.

## What is it?
* `main.c`: very simple main function that calls a function declared in
    `funcs.h`.
* `funcs.h`: declaration of two functions, one called, the other not.
* `funcs.c`: implementation of the functions.
* `Makefile`: make file to illustrate how to get the code coverage using
    the GNU GCC compiler suite.
* `Makefile.intel`: make file to illustrate how to get the code coverage
    using the Intel cmopiler suite.


## How to use?
Simply run
```bash
$ make coverage
```
See the `main.c.gcov` and `funcs.c.gcov` files for the coverage
information.
