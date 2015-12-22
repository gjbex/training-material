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
    and back references.
1. `StraightSql`: Example of how to interact with a relation database
    (SQLite3) using SQL from Python.
1. `create_sqlalchemy_db.py`: implements two classes representing SQL
    tables, and creates them in an RDBMS using SQLAlchemy's
    object-relational mapping mechanisms
1. `fill_sqlalchemy_db.py`: adds data using SQLAlchemy's ORM mechanisms
1. `query_sqlalchemy_db.py`: queries the RDBMS using SQLAlchemy's ORM
    mechanisms
1. `update_sqlalchemy_db.py`: illustrates updating values using SQLAlchemy's
   ORM mechanisms
