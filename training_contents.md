# Off the shelf training sessions

This is a (non-exhaustive) list of trainings offered on a regular basis
by the VSC, but also to research institutes and companies.

All of these trainings can be tailored to the audience if required,
and ad-hoc trainings are possible as well.


## C++ for scientific programming (14 hours)

This training focusses on using C++ for scientific programming and on
the way Bjarne Stroustrup advocates modern C++ in his book "A tour of
C++".  Some C++17 features and third party libraries will also be
discussed.

Subjects:

  * basics: control flow statements, data types, functions
  * user defined types: structs, classes
  * modularization of code
  * error handling
  * classes: inheritance 
  * templates
  * strings and regular expressions
  * I/O streams
  * STL containers and algorithms
  * numerics, Armadillo for linear algebra, GNU Scientific Library

Prerequisites:

  * experience in another programming language


## Fortran (7 hours)

Fortran is used a lot in the context of HPC.  For many, it has a
reputation of being an old and ugly programming language.  However,
modern Fortran is a far cry from Fortran 77 that its detractors have
in mind.  Fortran 2003/2008 is a language that is well tailored
towards scientific computing.  This training introduces the language
and its features.

Subjects:

  * basics: control flow statements, data types, functions
  * arrays and pointers
  * user defined types/classes
  * procedures
  * modules
  * file I/O
  * command line interaction
  * linear algebra with BLAS and Lapack

Prerequisites:

  * experience in another programming language


## Python trainings

### Python as a second language (4 hours)

Python is an all-round programming language that has applications in
many domains.  This training session introduces the programming
language to participants who have programming experience with other
programming languages such as R, MATLAB, C/C++ or Fortran.

Subjects:

  * control flow statements (conditional, repetition)
  * functions
  * data types
  * file I/)

Prerequisites:

  * experience in another programming language


### Python systems programming (4 hours)

Python is a very versatile programming language that has a wide range of
applications.  This training concentrates on interaction with the
operating system, the file system, other applications and the network.
This is useful for systems programming, but also when you want to use
Python as a coordination language for your workflows.

Subjects and Python modules that will be covered:

  * interacting with the operating system: os, platform, sys, psutil
  * interacting with the filesystem: os.path, pathlib, shutil,
    fileinput, tempfile
  * command line arguments & configuration files: argparse, configparser 
  * compressing & decompressing files: e.g., gzip, tarfile
  * running & communicating with other processes: sh, subprocess
  * running remote commands using SSH: paramiko

Prerequisites:

  * experience in Python programming


### Python software engineering (4 hours)

Quality of software matters, whether you share it with others or not.
Software should be easy to install, easy to use, and well documented.
This training will cover those aspects from the perspective of the
Python ecosystem.  However, it is also important that software is easy
to maintain, so coding style matters, API-level documentation should be
available, as well as a battery of tests to ensure the software's
integrity.  Of course, good design is at least as important.

Subjects and Python modules that will be covered:

  * code style and best practices, idiomatic Python: flake8, pylint
  * documentation: docstring, mkdocs
  * user interface: argparse, configparser
  * exception handling
  * type hints and type checking using mypy
  * unit testing: pytest
  * object oriented programming in Python
  * design patterns

Prerequisites:

  * experience in Python programming


### Scientific Python (4 hours)

Python is a nice programming language for scientific programming. Many
high quality libraries are available as building block in a wide variety 
of scientific domains. In this training we will concentrate on the core
libraries, and give some examples of domain specific libraries.

Subject and Python modules that will be covered:

  * multi-dimensional arrays and algorithms on these data structures:
    numpy
  * methods & algorithms useful for scientific programming, e.g., linear
    algebra, Fourier transforms, statistics, optimization, root finding,
    signal processing: scipy
  * symbolic computing: sympy
  * creating many types of plots: matplotlib
  * portable file formats for scientific data: e.g., HDF5
  * image processing: scikit-image

Prerequisites:

  * experience in Python programming


### Python for data science (4 hours)

Python is one of the dominant languages in data science.  In this
training we will cover a number of modules that are useful for data
preparation, analyzing data, visualization, and machine learning.

Subject and Python modules that will be covered:

  * representing, transforming & querying data: pandas
  * visualization: seaborn
  * parsing/cleaning data & regular expressions
  * machine learning: scikit-learn, keras

Prerequisites:

  * experience in Python programming


### Python for HPC (4 hours)

Although vanilla Python is fairly slow and hence not a good candidate,
there are several options to significantly increase the efficiency of
Python programs.

  * profiling Python code
  * using the numba JIT compiler
  * Cython to generate C code from annotated Python
  * implementing libraries in C, C++ and Fortran
  * concurrency via multiprocessing or concurrent.futures
  * parallelization using dask
  * distributed programming with mpi4py
  * data processing with pyspark

Prerequisites:

  * experience in Python programming
  * for some subjects, experience in programming C, C++ or Fortran


## Parallel programming

These courses have been developed by Rolf Rabenseifner (HLRS, Stuttgart,
Germany) and the training has followed Rolf's train-the-trainer program.

### MPI: Message Passing Interface (14 hours)

MPI is the de-facto standard for distributed parallel programming of
scientific applications.  It specifies language bindings for C and
Fortran.  This training covers the MPI 3.1 standard, but also
emphasizes potential pitfalls and best practices.

Subjects:

  * process model and language bindings
  * messages and point-to-point communication
  * non-blocking communication
  * collective communication
  * groups, communicators and virtual topologies
  * one-sided communication
  * shared memory
  * derived data types
  * parallel I/O
  * best practices

Prerequisites:

  * experience in C, C++ or Fortran programming


## OpenMP (7 hours)

OpenMP provides a very convenient programming model for scientific
applications that run multiple threads.  It is supported by C, C++ and
Fortran compilers.  Its main advantage is that it is mostly used through
annotation of code, which makes it easy to pick low hanging fruit when
starting to parallelize code. The training covers OpenMP 4.5, and
emphasizes pitfalls and best practices.

Subjects:

  * programming and execution model
  * worksharing directives
  * data environment
  * tasking
  * SIMD constructs
  * thread placement
  * pitfalls and best practices

Prerequisites:

  * experience in C, C++ or Fortran programming


## Defensive programming and debugging (4 hours + 2 hours optional)

All code contains bugs, finding and fixing them is boring.  In this
training, best practices are presented to reduce the number of bugs
in your code.  You will also learn about debuggers and debugging
techniques to find bugs more efficiently.

Subjects:

  * best practices in coding, code style, error handling
  * using compiler options to warn about potential issues
  * unit and functional testing
  * using a debugger (breakpoints, inspection, watchpoints, tracing, ...)
  * zoo of bugs
  * optional: debugging parallel code

Prerequisites:

  * experience programming C, C++, or Fortran 
  * familiarity with the bash command line
  * optional: experience using MPI and/or OpenMP


## Optimization (4 hours)

For HPC applications, performance is a major concern.  A thorough
understanding of the relevant hardware and software components is
required.  In this training, you will learn about a number of these
components, and how they influence the efficiency of you application.
You will also learn how to profile your application to identify
performance bottlenecks.

Subjects:

  * parallel efficiency 
  * memory: cache hierarchy, cache lines, memory access patterns,
    cache associativity
  * CPU: vectorization
  * pitfalls, e.g., double promotion, false sharing
  * feedback guided optimization
  * performance measures
  * profiling

Prerequisites:

  * experience programming C, C++, or Fortran 
  * experience using MPI and/or OpenMP
  * familiarity with the bash command line


## Linux bash shell (4 hours)

In HPC, most interaction with the systems is through the terminal and
a shell.  Working efficiently in such an environment saves a lot of time
and frustration.  In this training, you will learn the basics of bash,
as well as some Linux OS concepts.

Subjects:

  * interacting with files and directories
  * editors: nano, and hints at more sophisticated editors
  * process management
  * sharing: file and directory permissions
  * searching: find and grep
  * compressed files and archives: tar, gzip
  * copying to/from remote systems: scp, sftp, rclone

Prerequisites:

  * none


## Version control: git or SVN (4 hours)

Version control is an essential part of the software development process
and is crucial for scientific application to help reproducibility.
You will learn how to use a version control system (either git or SVN)
to document the changes in your source code.

Subjects:

  * motivation and advantages for using version control systems
  * how to use a version control system in a single user scenario
  * effective commit messages
  * commit history
  * how to use a version control system in a multi-user scenario
  * merge conflicts
  * branches and tags
  * tips and tricks

Prerequisites:

  * familiarity with the bash command line
