# DdtC

Some examples of code to debug with Arm Forge DDT.

## What is it?
1. `003_deadlock.c`: illustration of an application that has a
    deadlock.
1. `010_distributed_array.c`: mysteriously crashing application, use DDT
    memory checking to pinpoint problem.
1. `020_distributed_array.c`: complete example for illustrating DDT array
    view feature..
1. `030_distributed_array.c`: each process has a large matrix with some
    NaN values, can be found using DTD Statistics tab in the array viewer,
    and a filter.
1. `040_distributed_array.c`: this code doesn't have bugs, but can be
    used to illustrate how to use DDT to debug hybrid applicaitons.
1. `Makefile`: make file to build the code.
