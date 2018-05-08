# Itac
Sample code to illustrate the use of ITAC (Intel Trace Analyzer and
Collector) for debugging purposes.

## What is it?
1. `deadlock.c`: C application that deadlocks due to inappropriate
    order of send/receive calls.
1. `shift.c`: C application that is correct, but inefficient due to
    implicit serialization.
1. `Makefile`: make file to build the applications.
