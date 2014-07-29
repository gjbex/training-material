Refactoring Fortran code
========================

Often it is necessary to modify legacy Fortran code for better performance.
Here, a few techniques are illustrated.

What is it?
-----------
1. `legacy.f90`: the code exhibits a suboptimal access pattern to a rank 2
   array.
2. `data_mod.f90`: encapsulates a rank 2 array, and defines access methods
   that allow to retain the original indexing scheme, but that alter the
   access pattern to memory under the hood.
3. `refactored.f90`: refactored code.

