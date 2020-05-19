# F2py

`f2py` is a convenient way to use Fortran code from Python.

What is it?
-----------
* `array_utils.f90`: a Fortran module that defines a function to
    sum the elements of a double precesion array.  `f2py` creates
    a shared library and a wrapper file.
* `array_utils_f2py.py`: loads the module defined in the wrapper
    file and calls the `sum` function with a `numpy` array.
* `sum.f90`: Fortran program to test `array_utils.f90`
* `pi.f90`: Fortran function to compute pi from random numbers, `f2py`
    is used to create a shared library and a wrapper.
* `comp_pi_f2py.py`: test program to compute pi using a given number
    of iterations.
