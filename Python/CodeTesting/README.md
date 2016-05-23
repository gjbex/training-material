CodeTesting
===========

Python's standard library contains the `unittest` module, which allows
to easily implement unit testing, i.e., it is a framework for setting
up code for regression testing while developing, modifying, or refactoring
a code base.

What is it?
-----------
1. `constant_db.py`: implements a class that creates a database containing
    constants (mathematical or fysical), and defines a number of methods
    to query it.
1. `constant_db_test.py`: `unittest.TestCase` extension that implements a
    number of tests for the database.  The database is set up in the
    `setUp` method, and closed and removed in the `tearDown` method.
    Various tests are implemented to illustrate some of the assert methods
    defined by `unittest.TestCase`.
1. `run_test.sh`: shell script that actually runs the test code, and that
    uses discovery to minimize maintenance of test code.
1. `Asserts`: `assert` is a Python statement, so it not part of unit
    testing per se.  It is mainly intended for contract-based programming
    and one can prevent code to be emitted for asserts by using the
    `-O` optimizatino flag when running the code.

Note
----
The unit test that checks the number of entries in the database should
fail to illustrate the output.  Although there are only three constants
defined in the database, `pi` was added twice, so the total number of
rows is 4, not 3.
