# Profiling
The Python standard library offers the cProfile module, which can be used
to determine the functions that use most compute time.

The `line_profiler` gives more detailed information, but incurs substantial
overhead.  Hence it is best to use it only to profile the single function
the optimization process is currently focussing on.

The `memory_profiler` can be used to check which parts of programs or
functions use memory.

## What is it?
1. `primes_cprof.py`: Python script to profile using `cProfile`.
1. `primes_lprof.py`: Python script to profile using `line_profiler`.
1. `run_cprofile.sh`: Bash shell script to run the `cProfile`.
1. `run_kernprof.sh`: Bash shell script to run the `kernprof`
    `line_profiler`).
1. `run_snakeviz.sh`: Bash shell script to `cProfile`, save the profile
    to a file and invoke `snakeviz` to visualize it.
1. `run_mprof.sh`: Bash shell script to visualize memory usage as a function
    of time.
1. `run_memory_prof.sh`: Bash shell script to create a memory profile.
    Note that this generates a lot of overhead in terms of CPU time.
