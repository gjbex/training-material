# MemoryIssues
Code exhibiting various type of memory issues to illustrate using tools
such as Valgrind or Intel Inspector.

## What is it?
1. `leak.c`: simple code with a memory leak, caught easily by valgrind.
1. `memory_leak.c`: a slightly more involved memory leak illustration,
    mainly intended to allow memory consumption over time.
1. `array_bounds.c`: very simple, fail-sure example of exceeding array
    bounds.
1. `dangling_pointer.c`: simple example of using a dangling pionter,
    caught easily by valgrind. Application termintates with segmentation
    fault.
1. `Makefile`: make file to build using GCC.
