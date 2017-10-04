# Pitfalls
These are code samples illustrating various pitfalls when using Python.

## What is it?
1. `non_trivial_default.py`: using a `list` or similar data structure as
    a default argument to a list leads to unexpected behavior since the
    default value is created at module load time only, and hence persists
    between function calls.
