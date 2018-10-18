# Semantics

Different (or incorrect) interpretation of programming language
semantics may lead to bugs.

## what is it?
1. `side_effects.f90`: should both operands of Fortran's logical `.and.`
    and `.or.` operators be evaluatee, and in whaat order?
1. `run_side_effects_gcc.sh`: script to compile `side_effects.f90` with
    `gfortran` and run the application.
1. `run_side_effects_intel.sh`: script to compile `side_effects.f90`
    with `ifort` and run the application.
1. `Makefile`: make file to build the application.
