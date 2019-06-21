# Ctypes

The ctypes Python standard library module is convenient
to wrap simple shared library functions.

## What is it?

* Logistic map
    1. `logistic_map.h`: declaration of the logistic map function.
    1. `logistic_map.c`: implementation of the logistic map function.
    1. `Makefile`: make file to build the shared library containing
        the logistic map function.
    1. `log_map_cdll.py`: Python script that loads and calls the
        logistic map function in the shared library.
    1. `field.py`: another more computationally intenisve Python script
         using the logistic map function.
* `libmy_stuff.so`: dynamic library containing a somewhat bizarre
   collection of functions.
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
   * `point.py`: defines a Python class for a point corresponding to
     the C structure and computes the distance between two points.
   * `stats.py`: computes the descriptive statistics for a 5 and a 3
     element array.

## Note

To run the C test programs, add the current working directory to
`LD_LIBRARY_PATH` so that the shared library can be loaded succesfully.
* `libmy_stuuf.so`:
