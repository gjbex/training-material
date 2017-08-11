# Ufunc
An ufunc is a function that can be applied to numpy arrays. It operates
element-wise on array elements. An ufunc supports reduction, accumulation,
and broadcasting automatically.

Creating your own ufunc can be done in C or Cython, but is cumbersome, to
say the least. numba defines decorators to simplify the definition of a
ufunc considerably.

## What is it?
1. `julia_set.py`: driver program used to run the various implementations,
    selectable by command line option.
1. `julia_python.py`: Python implementation of Julia set computation.
1. `julia_ufunc.py`: numba implementation of Julia set computation.
1. `julia_numba_eager.py`: numba implementation of Julia set computation
    as a generalized ufunc.
