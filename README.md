# Training material

A collection of code examples for training purposes, mostly in the
context of data processing and parallel programming.

This material is made available as is, i.e., anyone is welcome to use it,
and to [contribute](CONTRIBUTING.md).  However, no support is guaranteed
in any form.  All material is subject to the [license](LICENSE) included
in this repository.

Tips and tricks can be found on this [repository's website](http://gjbex.github.io/training-material/)
but also in a [cheat sheet repository](https://github.com/gjbex/Cheatsheets).

An overview of all off-the-shelf training sessions is also
[available online](https://gjbex.github.io/Training-sessions/).

[![DOI](https://www.zenodo.org/badge/18587808.svg)](https://www.zenodo.org/badge/latestdoi/18587808)


## What is it?

### Accelerators
[`Accelerators`](Accelerators): some sample code and information on using
accelerators.

### C
[`C`](C): presentation based "The C programming language" by Kernighan and
Ritchie, as well as sample code to illustration the concepts.

### C++
[`CPlusPlus`](CPlusPlus): presentation based on "A tour of C++" by Stroustrup,
as well as sample code to illustrate the concepts.  This part of the repository
is considered obsolete and has been replaced by another repository for a C++ for
scientific programming training.  See
* [training website](https://gjbex.github.io/Scientific-C-plus-plus/)
* [repository](https://github.com/gjbex/Scientific-C-plus-plus)

### Data storage
[`DataStorage`](DataStorage): sample code showing how to read/write HDF5 and
NetCDF files from C, Fortran, and Python.  HDF5 can be used for parallel
I/O, C sample code is provided.  The HDF5 material is part of a tutorial on
that subject.  Sample code on how to interact with a redis data
structure server is also provided, illustrating the hiredis C API.
Sample SQL covers the basics of querying relational databases

### Debugging
[`Debugging`](Debuggers): slides used for an info session on debugging tools
and techniques, as well as sample code.  This part of the repository is
supplemented by the following repository:
* [Defenesive programming and debugging](https://github.com/gjbex/DPD-online-book)

### Fortran
[`Fortran`](Fortran): presentation on "Modern Fortran" as well sample code
intended to illustrate Fortran 95, 2003, and 2008 features.  This section
of the repository has been superceeded by two other repositories:
* Fortran for programmers
  * [website](https://gjbex.github.io/Fortran-for-programmers/)
  * [repository](https://github.com/gjbex/Fortran-for-programmers)
* Fortran MOOC
  * [website](https://www.futurelearn.com/courses/fortran-for-scientific-computing)
  * [repository](https://github.com/gjbex/Fortran-MOOC)

### Java
[`Java`](Java): sample code mostly for demonstration purposes.

### Linux Tools
[`LinuxTools`](LinuxTools): some illustrations of using Linux tools such as
the `M4`macro processor, make files and autotools, as well as slides on
version control using svn and git.

### Mathematics
[`Math`](Math): sample code for using various mathematical libraries.

### Miscellaneous
[`Misc`](Misc): catch-all for one-time presentations, or special sessions.

### MPI
[`Mpi`](Mpi): illustration of distributed programming using the Message
Passing Interface API.

### OpenMP
[`OpenMP`](OpenMP): sample code for OpenMP.

### Optimization
[`Optimization`](Optimization): illustrations of performance optimization
opportunities.  This section of the repository has been superceeded by a
training repository on code optimization.
* [website](https://gjbex.github.io/Code-optimization/)
* [repository](https://github.com/gjbex/Code-optimization)

### PBS
[`PBS`](PBS): sample PBS torque batch scripts to illustrate features.

### Python
[`Python`](Python): sample code to explore various Python features, standard
library packages and third party libraries.  Most of this material is
used in a tutorial on using Python for scientific data processing.  This part of
the repository has in large part been superceeded by various training 
repositories dedicated to specific Python-related topics.
* Python for programmers
  * [repository](https://github.com/gjbex/Python-for-programmers)
* Scientific Python
  * [website](https://gjbex.github.io/Scientific-Python/)
  * [repository](https://github.com/gjbex/Scientific-Python)
* Python for data science
  * [website](https://gjbex.github.io/Python-for-data-science/)
  * [repository](https://github.com/gjbex/Python-for-data-science)
* Python for machine learning
  * [website](https://gjbex.github.io/Python-for-machine-learning/)
  * [repository](https://github.com/gjbex/Python-for-machine-learning)
* Python for HPC
  * [website](https://gjbex.github.io/Python-for-HPC/)
  * [repository](https://github.com/gjbex/Python-for-HPC)
* Python for systems programming
  * [website](https://gjbex.github.io/Python-for-systems-programming/)
  * [repository](https://github.com/gjbex/Python-for-systems-programming)
* Python software engineering
  * [website](https://gjbex.github.io/Python-software-engineering/)
  * [repository](https://github.com/gjbex/Python-software-engineering)

### R
[`R`](R): some very simple illustrations of how to run R scripts from the
command line, and to submit as (PBS) jobs

### Virtualization
[`Virtualization`](Virtualization): Information on how to use Singularity.
This part of the repository has been superceeded by a training repository
on using containers for HPC.
* [website](https://gjbex.github.io/Containers-for-HPC/)
* [repository](https://github.com/gjbex/Containers-for-HPC)

### Visualization
[`Visualization`](Visualization): data files, XDMF files and ParaView state
files to use during a demo of scientific visualization with ParaView.


## Contributors

* Geert Jan Bex ([geertjan.bex@uhasselt.be](mailto:geertjan.bex@uhasselt.be)),
  Hasselt University/University of Leuven
* Stefan Becuwe, University of Antwerp
  * suggestions for and correction of typos in Python presentation
  * suggestions for Python programming exercises
* Guillaume Jacquenot
  * Python 3 version of XDMF generating scripts
  * correcting typos in various README
  * suggesting hyperlinking the README files, and providing a Python script for
    it
* Arnout Standaert, VITO
  * update of deprecated Pandas API
  * suggestions on Python OOP presentation section
* Yana Maneva, KU Leuven
  * suggestions on online C++ training material references


You are very welcome to contribute, please read
[some guidelines](CONTRIBUTING.md) before you do.
