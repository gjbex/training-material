# Orm
Sample object-relational mapping (ORM) code implemented in Pythno's
`sqlalchemy`.  Note that the database schema is not the same as that of
the SQL examples in the parent directory.

TODO: make schemas on slides, in SQL examples and ORM code consistent

## What is it?
1. `experiments.py`: class definitions for experiments, researchers and
    samples, taking into account their associations.
1. `create.py`: create database schema.
1. `fill.py`: add some data to the database, illustrating back references.
1. `view.py`: illustrate using back references when using objects.
1. `orm_utils.py`: some helper functions for more convenient ORM usage.
1. `shell.py`: a shell to work with the database using a domain specific
    language.
