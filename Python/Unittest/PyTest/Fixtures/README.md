# Fixtures
A simple illustration of using fixtures in pytest.

## What is it?
1. `test_data_structure.py`: creates a test and a module fixture, and
    defines three tests, one of which is intended to fail.
1. `test_wc.py`: creates a module fixture that will be torn down when
    the test is done.

## How to use?
Simply run pytest:
```bash
$ pytest -q
```
The `-q` option suppresses extra pytest information.
