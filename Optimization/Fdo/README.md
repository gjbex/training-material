# Fdo
Feedback Directed Optimization can be useful to squeeze some extra
peformance out of an application.  An instrumented version of the
application is build and run, which produces runtime profile information
that is used in a subsequent build to guide the optimization process.

Note that the run using the instrumented code must be representative
for the actual workload of the application.

## What is it?
1. `cache_hierarchy.c`: a simple C application that times array
    operations as a function of their size to illustrate the cache
    hierarchy (L1, L2, L3 and RAM) on modern CPUs.
1. `test_fdo.pbs`: a PBS torque script (can be run in bash as well, of
    course) that
  * builds the application using `-O3` optimization, runs it, and
    produces an output file with timing information.
  * builds an instrumented version of the application, runs it to
    produce profile information.
  * builds an optimized version using the profile information, runs it,
    and produces an output file with timing information.
1. `test_fdo.plt`: gnuplot script to compare the timings for the `-O3`
    and FDO version of the application.
