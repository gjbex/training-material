# Fixtures
Fixtures can be defined in CUnit on the level of suites, i.e., the
initialization is run once before the start of the first test in the
suite, the cleanup once after the last test has finished.


## What is it?
1. `tests.c`: CUnit tests using a fixture.
1. `Makefile`: make file to build the code.


## How to use it?
To run without feedback on when the fixture is created, simply make:
```bash
$ make
```

To have the application print a message when the initialization and the
cleanup functions are run, build with:
```bash
$ make CFLAGS="-D VERBOSE"
```
