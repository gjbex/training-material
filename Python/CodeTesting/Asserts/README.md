# Asserts

`assert` is a Python statement, so it not part of unit testing per se.
It is mainly intended for contract-based programming and one can prevent
code to be emitted for asserts by using the `-O` optimizatino flag when
running the code.

## What is it?
1. `fac.py`: implements factorial function, checking whether the
    argument is of type integer, and positive using asserts.
1. `run.sh`: Bash shell script to run the Python code, once with, and once
    without code generated for assertions.
