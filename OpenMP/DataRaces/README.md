# DataRace
The code samples included illustrate some simple examples of data races.
They can be used to demo Intel Inspector.

## What is it?
1. `pi1.f90`: data races on `pi_sum`, `thread_num`, and `num_threads`
    variables.
1. `pi2.f90`: using `reduction` the data race on `pi_sum` has been
    eliminated, but the other errors are still present.
1. `pi3.f90`: all data races eliminated.  Note that the assumption is made
    that the schedule will be `static`.
1. `pi4.f90`: the schedule is set to `tuntime` to allow illustrating how
    the assumption will lead to errors.
1. `Makefile`: make file to build the code.
