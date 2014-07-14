Context manager
===============

A context manager can be used to initialize and finalize resources.  Once
defined, they can be used with Python's `with` construct.

What is it?
-----------
`context.py`: illustrates two ways to define a context manager,
* as a class, providing hooks on instantiation, entering, and exiting
  the context.
* as function decorator, where code to be executed for initialization,
  entering, and exiting sandwiches a `yield` statement that returns the
  value.

