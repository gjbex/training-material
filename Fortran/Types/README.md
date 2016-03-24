Fortran types
-------------

What is it?
-----------
1. `single` and  `double`: both applications are compiled from
    `types_test.f90` using the preprocessor to use either single or
    double precision real numbers.  It also illustrates the `REAL32`
    and `REAL64` constants defined in the `iso_fortran_env` module
    to use as kind in declarations of real numbers.
1. `rand_test`: generates a list of random numbers from a normal
    distribution using the Box-Muller algorithm.  The subroutine
    `random_normal_number` in the `random_mod` module uses the `save`
    attribute to keep track of each second number that is generated
    for the next call, and the state of the generator.
1. `particle_sim`: sets up an given number of particles that have a
    position in 3D (random uniform), a velocity (random normal), a mass
    (random uniform) and a charge (random uniform).  The latter is
    an integer property, all others are real valued.
    The particles are stored in variable of a user defined type that
    contains an array for each property (structure of arrays), defined
    in the `particles_mod` module.  Besides the type definition, the
    latter also contains subroutines to initialize, print, and delete
    the particles.
1. `precision_test`: although the single and double precision kind
    constants are defined in the `iso_fortran_env` module, the latter
    might not always be available.  This code illustrates two alternative
    approaches and compares the results with `REAL32` and `REAL64`.
1. `complext_test`: shows single and double precision complex number
    declarations.
1. `limits_test`: shows numerical model paraemters for integers and reals
1. `infinity_nan_test`: illustrates infinity and NaN results of floating
    point computations
1. `default_type_test`: check which real number type `REAL` defaults to.

How to build?
-------------
A make file is provided.

To build a `infinity_nan_test` that uses `ieee_arithmetic`, define
`IEEE_STUFF`, i.e.,
```
make FFLAGS='-DIEEE_STUFF infinity_nan_test
``` 
Note: not all compiler version support this yet.
