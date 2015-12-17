# Fixtures
In unit testing, fixtures can be run to setup and tear down an envirenment
before and after running each test.  Similarly, a set up and tear down can
be done on class and module level.  The code here illustrates all three
levels.

## What is it?
1. `create_db.sql`: SQL statements to create database tables (SQLite3).
1. `fill_db.sql`: SQL statements to insert initial data into the tables
    (SQLite3).
1. `init.py`: this will create the database to test on.
1. `tests.py`: series of tests to ensure that the database is filled
    with the desired information; a second series of tests checks column
    constraints, table constraints, and triggers.

## How to use?
Run all tests:
```bash
./tests.py
```
The database can be created independently of the tests as well:
```bash
./init.py  projects.db  --create create.sql  --fill fill.db
```
