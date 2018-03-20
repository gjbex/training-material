# Const

The use of `const` in C/C++ is a bit more subtle then some might realize.
This is some code to illustrate that point.

The semantics of `const` in the following code fragment is that the values
the pointer refers to are constant.
```c
void do_something(const double *v, int n);
```
In this function, the values of the array can not be modified.  However,
a new value can be assigned to the variable `v` in this function's body.

The semantics of `const` in the code fragment below is different.  It
implies that the variable `v` is constant, but the values in the array can
in fact be modified.
```c
void do_something(double * const v, int n);
```

Hence the following declaration will ensure that neither the variable `v`,
nor the array values it points to can be modified.
```c
void do_something(const double * const v, int n);
```

## What is it?
1. `const_double_pointer_nok.c`: this code will not compile, since the
    content of the array is modified.
1. `const_double_pointer.c`: this code will compile, since only the
    value of the function's argument is modified, not the content of the
    array.
1. `double_pointer_const_nok.c`: this code will not compile, since the
    value function's argument is modified.
1. `double_pointer_const.c`: this code will compile, since the value
    function's argument is not modified, but the contents of the array can
    be modified.
1. `const_double_pointer_const_nok.c`: this code will not compile since it
    tries to modify both the function argument, and the array values the
    former points to.
1. `utils.h`: header file declaring auxillary functions.
1. `utils.c`: auxillary function defintions.
1. `Makefile`: make file to build the applications, and reproduce the
    error messages.

## How to use?
To build the applications, simply use `make`:
```bash
$ make
```

To reproduce the errors, use:
```bash
$ make -k errors
```
