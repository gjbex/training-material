# Fixtures
In unit testing, fixtures can be run to setup and tear down an envirenment
before and after running each test.

## What is it?
1. `create_db.sql`: SQL statements to create database tables (SQLite3).
1. `fill_db.sql`: SQL statements to insert initial data into the tables
    (SQLite3).
1. `content_test.py`: series of tests to ensure that the database is filled
    with the desired information.  It requires the existence of
    `projects.db`, initialized by the queries in `create_db.sql`,
    followed by `fill_db.sql`.
1. `constraints_test.py`: series of tests for column constraints, table
    constraints, and triggers.
