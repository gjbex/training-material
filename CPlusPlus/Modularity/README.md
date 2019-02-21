# Modularity
Code illustrations for chapter 3, Modularity in Stroustrup's
"A tour of C++".

# What is it?
1. `NamespaceParticles`: example of defining a namespace.
1. `Patricles`: example of separate compilation.
1. `Stats`: example of separate compilation.
1. `fac.cpp`: illustrates exception handling.
1. `memory_leak.cpp`: illustration of a memory leak caused by bad exception
    handling.
1. `memory_leak_fixed.cpp`: illustrates using RAII to ensure correct resource
    management.
1. `Makefile`: make file for these examples.

## How to use it?
Run `memory_leak.exe` and `memory_leak_fixed.exe` through valgrind with -1 and 5
as arguments and note the difference.
