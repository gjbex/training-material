# Doxygen
Illustration of generating API level documentation using doxygen.
This is an example for Fortran.

## What is it?
1. `doxygen.conf`: doxygen configuration file for this project.  Note
    that a few settings had to be changed to ensure that doxygen works
    correctly on Fortran (`OPTIMIZE_FOR_FORTRAN` but also
    `EXTENSION_MAPPING` to ensure that Fortran files are parsed as
    free-style Fortran.
1. `mainpage.dox`: file containing the contents of the main
    documentation page.
1. `node_mod.f90`: documented Fortran 2003 module implementing a node
    type for building binary trees, as well as some algorithms on trees.

## How to use?

To generate the documentation, use
```bash
$ doxygen doxygen.conf
```
This will generate both HTML and LaTeX documentation.  For the latter,
a `Makefile` is generated to typeset it and produce a PDF document.
