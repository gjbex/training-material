# AttributeAccess
Illustration of how restricting access to object attributes can protect
object state, and hence prevent bugs.

## What is it?
1. `stats_mod.f90`: definitino of a class to accumulate statistical
    information on a stream of values.
1. `stats.f90`: main program illustrating how inappropriate object
    attribute access can compromise the object's state.
1. `stats_private_mod.f90`: definitino of a class to accumulate statistical
    information on a stream of values.  In this implementation, object
    attributes are private.
1. `stats_private.f90`: main program illustrating how inappropriate object
    attribute access can compromise the object's state.  Since private
    attributes are accessed, this code will intentionally fail to compile.
1. `Makefile`: make file to build the applications.
