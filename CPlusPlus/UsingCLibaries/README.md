# UsingCLibraries
This code sample illustrates how to use a C library, GSL in this case,
from C++.

## What is it?
1. `cannon_max_range.cpp`: C++ application to compute the angle that
    yields the maximum range for artillery, where air drag and density
    are taken into account. GSL is used to solve the set of ordinary
    differential equations, and to find the extremum of the range function.
1. `Makefile`: make file to build the application.
