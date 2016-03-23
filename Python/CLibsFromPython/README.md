# Using C libraries from Python
It is fairly (although not completely) straightforward to call C functions
in a library from Python code.  Examples are given of how to deal
with simple data types, arrays and structures as arguments or return
values.

## What is it?
To create the library, use the provided `Makefile`.

1. `libmy_stuff.so`: dynamic library containing a somewhat bizarre
   collection of functions.
  * `logistic_map.[ch]`: implementation of the logistic map function
    `log_map` that takes two `double` and an `int` argument.
  * `point.[ch]: declares a structure representing a point in 2D with
    and x and a y field, both `double`.  A function `distance` is
    defined that takes to variables of type `Point`.
  * `stats.[ch]`: declares a structure to represent statistical descriptive
    data (mean, standard deviation and number of data points), as well
    as a function, that given an array of `double` and its `int` length,
    computes these quantities and returns them.
1. `..._main.c`: main files that provide test applications for the C
   libraries.
1. Python scripts using the library.
   * `log_map.py`: computes the logistic map for fixed parameters.
   * `field.py`: computes the logistic map for a range of range of values.
   * `point.py`: defines a Python class for a point corresponding to
     the C structure and computes the distance between two points.
   * `stats.py`: computes the descriptive statistics for a 5 and a 3
     element array.

## Note
To run the C test programs, add the current working directory to
`LD_LIBRARY_PATH` so that the shared library can be loaded succesfully.
