# Preprocesing
The C preprocessor can be used for Fortran.

## What is it?
1. `preprocessing.f90`: Fortran code with conditional compilation.
1. `Makefile`: make file to build either version of the application.
1. `build_without_bye.sh`: shell script to build the version where the
    macro is undefined.
1. `build_with_bye.sh`: shell script to build the version where the
    macro is defined.
