# MemoryIssues
Code exhibiting various type of memory issues to illustrate using tools
such as Valgrind or Intel Inspector.

## What is it?
1. `leak.c`: simple code with a memory leak, caught easily by valgrind.
1. `memory_leak.c`: a slightly more involved memory leak illustration,
    mainly intended to allow memory consumption over time.
1. `leak.txt`: monitor output for `memory_leak.exe`.
1. `plot_leak.py`: Python script to plot memory usage in `leak.txt`.
1. `array_bounds.c`: very simple, fail-sure example of exceeding array
    bounds.
1. `dangling_pointer.c`: simple example of using a dangling pionter,
    caught easily by valgrind. Application termintates with segmentation
    fault.
1. `null_pointer.c`: simple example of a non-checked, failed `malloc`,
    caught easily by valgrind. Application termintates with segmentation
    fault.
1. `stack_issue.c`: function returns stack variable, which makes the
    caller segfault, can be caught using valgrind.
1. `Makefile`: make file to build using GCC.
