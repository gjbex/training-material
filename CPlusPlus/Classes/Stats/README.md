# Stats
Illustration of inheritance where the derived class calls the constructor
as well as a method from the base class.  Illustrates defining `super`.

## What is it?
1. `simple_stats.h`: base class definition implementing a streaming
    average computation of the mean value.
1. `simple_stats.cpp`: base class implementation implementing a streaming
    average computation of the mean value.
1. `stats.h`: derived class definition implementing a streaming
    average computation of the standard deviation as well as the mean
    value.
1. `stats.cpp derived class implementation implementing a streaming
    average computation of the standard deviation as well as the mean
    value.
1. `main_stats.cpp`: main program to illustrate the use of `SimpleStats`
    and `Stats` classes.
1. `Makefile`: make file to build the executable.
