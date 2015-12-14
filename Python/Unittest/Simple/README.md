# Simple
A straightforward illustration of the assert functions in the `unittest`
module.

## What is it?
1. `func_lib.py`: a library module containing functions to be tested.
1. `run_tests`: a Bash shell script to run all tests.
1. `fib_test.py`: test for the `fib_fast` function, illustrates
    `assertEqual` with `msg` argument, `assertRaises`.  Also note the
    `from ... import ... as ...` construct.
1. `fib_test.py`: test for the `fib` function, illustrates `assertEqual`
    with `msg` argument, `assertRaises`.
1. `pi_test.py`: test for the pi function, illustrates
    `assertAlmostEqual`.
1. `is_primes_test.py`: test for the`is_prime` function, illustrates
    `assertTrue` and `assertFalse`.  Test for non-prime numbers will fail
    for illustration.
1. `primes`: test for the `primes` function, illustrates
    `assertListEqual`.  Test will fail as a consequence of the problem in
    `is_prime_test.py`.
