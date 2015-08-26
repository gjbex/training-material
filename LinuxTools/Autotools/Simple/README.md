Autotools: trivial example
==========================

This is a trivial example of using autotools for creating build
infrastructure.

What is it?
-----------
1. `configure.ac`: autoconfig file used to generate the configure script,
    note that it should list all make files to be created.
1. `Makefile.am`: automake file that describes the make file to be
    generated in the root directory, only lists the subdirectory to build
    in this case.
1. `src`: source directory with four Fortran files, two main programs, and
    two modules.
1. `src/Makefile.am`: automake file to create the make file to actually
    build the software, lists targets, and the source files they depend on.
1. `prepare.sh`: shell script to generate configure.
1. `cleanup.sh`: shell script to remove all autotool artefacts.

How to use?
-----------
1. Generate the configure script: `$ ./prepare.sh`
1. Run configure: `$ ./configure --prefix=$HOME/tmp/test`
1. Build and install: `$ make install`
