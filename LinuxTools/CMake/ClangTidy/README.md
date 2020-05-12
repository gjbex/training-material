# ClangTidy

Illustration of how to invoke clang-tidy on a code base.

## What is it?

1. `state.h`: class definition representing states for the N-queens
   problem.
1. `state.cpp`: method definitions for the `State` class.
1. `nqueens.cpp`: recursive implementation of backtracking algorithm
   for the N-queens problem.
1. `CMakeLists.txt`: CMake file to build the application and run
   clang-tidy.
