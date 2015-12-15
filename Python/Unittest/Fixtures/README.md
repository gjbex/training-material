# Fixtures
In unit testing, fixtures can be run to setup and tear down an envirenment
before and after running each test.

## What is it?
1. `create_db.sql`: SQL statements to create database tables (SQLite3).
1. `fill_db.sql`: SQL statements to insert initial data into the tables
    (SQLite3).

## Requirements
Note that this will only work with SQLite 3.9.x or later.
