Fortran
=======

This is work in progress for an information session on modern Fortran
(95, 2003, 2008).  Prior knowledge of Fortran 77/90 is assumed.

This may grow over time to become a full-fledged Fortran course.

Contents
--------
1. `ControlStructures`: illustrations of how to use Fortran's control
    statements (`DO`, `DO WHILE`, `FORALL`, `WHERE`, `IF`, `SELECT CASE` and
    `BLOCK`.
1. `Functions`: illustrates how to define procedures, internal versus
    module procedures, pure and elemental procedures, recursion,
    interfaces for using higher order functions.  Also contains some
    code to time arithmetic operations and Fortran intrinsic math
    fucntions.
1. `Integrate`: illustration of extension of abstract type, and
    implementation of abstract interface.
1. `IO`: illustrates Fortran's I/O mechanisms, sequential read/write of
    formatted and unformatted records, stream read/write of unformatted
    records.
1. `Julia`: illustration of using complex arithmethic and elementary
    functions.
1. `Matrices`: illustrates array operations and intrinsic functions
    operating on arrays, indexing by slices,  as well as allocatable arrays.
1. `Miscellaneous`: Dealing with command line arguments, environment
    variables.
1. `modern_fortran.pptx`: Microsoft Powerpoint presentation of modern
    Fortran features intended for those not familiar with some of the
    features introduced in Fortran 95, 2003, and 2008, or for those who
    typically program in C/C++, but want to get a flavor of Fortran's
    capabilities and particularities.
1. `OOProgramming`: an illustration of how to define a tree data structure
    using classes and inheritance.  A second example shows a naive
    implementation of rational numbers to illustrate operator overloading.
1. `Preprocessing`: illustration of how to use the C preprocessor in
    Fortran.
1. `Refactoring`: shows how to fix legacy code with a suboptimal array
    access pattern by encapsulating the array.
1. `Types`: illustrates the various basic data types such as `REAL`,
    `COMPLEX`, `INT`, and their limits and precision, as well as how
    to detect numerical overflow and undefined arithmetic operations.
    Type conversion and user defined types are illustrated as well.
