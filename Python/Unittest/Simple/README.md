# Simple
A straightforward illustration of the assert functions in the `unittest`
module.

## What is it?
1. `func_lib.py`: a library module containing functions to be tested.
1. `run_tests`: a Bash shell script to run all tests.
1. `fib_fast_test.py`: test for the `fib` function, illustrates
    `assertEqual` within a `subTest`.
1. `pi_test.py`: test for the pi function, illustrates
    `assertAlmostEqual`.
1. `is_primes_test.py`: test for the`is_prime` function, illustrates
    `assertTrue` and `assertFalse`.  Test for non-prime numbers will fail
    for illustration in cases 0 and 1 (`subTest` context is used).
1. `primes`: test for the `primes` function, illustrates
    `assertListEqual`.  One test will fail as a consequence of the
    problem in `is_prime_test.py`, the other because an exception is not
    raised..
