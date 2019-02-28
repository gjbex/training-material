# LateBinding

Example of a base class and a derived class where late binding is required.

## What is it?

1. `stats.h`: defintion of a class to compute trivial statistics on a data
   stream.
1. `stats.cpp definition of member functions of the `Stats` class.
1. `median_stats.h`: defintion of a class derived from `Stats` that adds the
   ability to compute the median.
1. `median_stats.cpp defintion of member functions of the `MeidanStats` class.
1. `stats_main.cpp`: application that computes statistics on data read from
   standard input.  If the `-m` option is specified on the command line, it
   will also compute the median in addition to the trivial statistics.
1. `Makefile`: make file to build the application.
1. `data.txt`: small data file to test the application.
