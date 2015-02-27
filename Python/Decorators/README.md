Decorators
==========

Python supports decorators, i.e., function wrapping to add functionality
before and/or after the function's invocation.  Python comes with a number
of standard decorators, but it is easy to define one's own.

What is it?
-----------
1. `decorators.py`: two decorators are defined to check a wrapped
    function's arguments.  The first, `check_min` throws and exception
    when the argument is negative, the second, `check_max`, throws another
    exception when the function is called with an argument that is too
    large.  The decorated function is this example is the factorial.
1. `memoize.py`: an example of adding a cache to a function using a simple
    decorator
