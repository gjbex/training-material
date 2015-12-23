Database access
===============

Accessing relational database systems from Python is straighforward.  The
Python standard library comes with a simple in-memory relational database
system SQLite via de `sqlite3` module.
Other RDBMS can be accessed similarly using SQLAlchemy.

However, SQLAlchemy also support an object-relational mapping approach,
which is also illustrated by sample code.


What is it?
-----------
1. `ExperimentDB`: Example of SQLAlchemy's object-relational mapping,
    illustrating declarative schema definition, bidirectional associations
    and back references.  Also adds a shell to manipulate the database
    using a domain specific language.
1. `Orm`: simple illustration of SQLAlchemy's ORM approach.
1. `StraightSql`: Example of how to interact with a relation database
    (SQLite3) using SQL from Python.
