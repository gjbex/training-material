# Qmtest
Simple illustration of using QMTest for integration testing.

## What is it?
1. `fac.py`: Python application under test.
1. `Makefile`: make file to initilize the QMTest database and define
    tests, run them and perform cleanup.

Note: reatures such as requirements are not reliably implemented.

## How to use?
1. Set up the tests using `make init`.
1. Run the tests using `make run`.
