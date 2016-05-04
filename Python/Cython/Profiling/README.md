# Profiling
Cython code can be profiled using `cProfile`, just like regular Python
code.  In addition, the compiler can annotate Cython code to highlight
code fragmens that are Python-heavy, and hence good targets for
optimization.

## What is it?
1. `quad_pure.py`: Python implementation as base reference.
1. `quad.pyx`: No Cython profiling enabled.
1. `quad_prof.py`: Profiler globally enabled.
1. `quad_prof_indiv.py`: Profiler enabled for a single function  only,
    using a decorator.
1. `run_quad.py`: Python script to drive the various iplementations for
    profiling.
1. `setup.py`: Python build file for the Cython code
1. `Makefile`: build file to compile Cython files, and clean installation.
1. `run_profile.sh`: Bash script to run the code for profiling.
1. `annotate.sh`: Bash script to create the HTML annotation file.
