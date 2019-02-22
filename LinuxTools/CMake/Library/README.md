# Library

Example of a project that builds a shared library and two executables.  It will
install the executables, the library and the header files.

## What is it?

1. `src`: source directory
  1. `stats_main.cpp`: defines the main function of an application that reads
     data from standard input, and writes statistics to standard output.
  1. `table_stats_main.cpp`: defines the main function of an application that
     reads column data from standard input, and writes statistics to standard
     output.
  1. `CMakeLists.txt`: CMake file to build and install the executables.
  1. `stats`: source directory for the library that defines the `Stats` and
     `TableStats` classes.
    1. `stats.h`: class defintion for `Stats`
    1. `stats.cpp method defintion for `Stats`
    1. `table_stats.h`: class defintion for `TableStats`
    1. `table_stats.cpp method defintion for `TableStats`
    1. `CMakeLists.txt`: CMake file to build and install the shared library and
       install the header files.
1. `CMakeLists.txt`: CMake file to build and install the project.
1. `build.sh`: bash script to build the project.
