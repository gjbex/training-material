# Diffusion
Illustration of dependency handling for C++ code, especially with respect
to header files.

## What is it?
* `particles.h`: ensemple of particles representation.
* `particles.cc`: implementation.
* `constrained_particles.h`: ensemple of particles representation.
    Subclass of `Particles` that are constrained in a box.
* `constrained_particles.cc`: implementation.
* `statistics.h`: class to handle computing the relevant statistics.
* `statistics.cc`: implementation.
* `distribution.h`: class to handle position distributions and
    compute the entropy.
* `distribution.cc`: implementation.
* `walk.cc`: statistical properties of randmo walk over time.
* `distr.cc`: compute distribution of particle positions.
* `entropy.cc`: entropy over time.
* `Makefile`: illustrates handling C++ dependencies.
