# Tasks

Illustrations of task-based parallelism in OpenMP.

## What is it?
1. `fib-tasks.c`: recursive implementation of the Fibonnaci function
    using tasks to handle recursive calls.  Due to overhead this doesn't
    scale very well, apart from the fact that computing Fibonnaci numbers
    recursively is not exactly one's best approach.
