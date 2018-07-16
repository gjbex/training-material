# Simple
A very simple illustration of using the `pytest` unit testing framework.

## What is it?
1. `fac.py`: defines two implementations of the factorial function, and
    is a script to compute its value for 0 up to a value specified on the
    command line.  One of the implementations doesn't raise an exception
    when called with a negative number.
1. `test_fac.py`: `pytest` code to test `fac.py`.
1. `distance.py`: defines a function that computes the distance between
    two points.  The points are represented as a 2-tuple (Carthesian
    coordinates.
1. `test_distance.py`: `pytest` code to test `distance.py`. One test
    will fail by design.


## How to use it?
Make sure `pytest` is installed, run it with:
```bash
$ pytest
```
