# Numba
numba provides a just-in-time compiler (JIT) for Python code. Functions can be
decorated to indicate that they should be compiled.  Fairly impressive speedups
can be obtained without much effort.


## What is it?
1. `numba_test.py`: some timing tests for numpy constructs, including the
    use of numba.
1. `JuliaSet`: Julia set code implementation comparing a pure Python
    implementation with numba JIT and eager JIT.
1. `Primes`: code to compute the first n prime numbers comparing a pure Python
    implementation with numba JIT and eager JIT.
1. `Ufunc`: defining a numpy ufunc using numba.
