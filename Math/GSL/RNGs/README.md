# RNGs
Examples of generating random number from a distribution.

## Contents
1. `generate_exp_distr.c`: generate random number from an exponential
    distribution.
1. `generate_uniform_distr.c`: generates random numbers from a uniform
    double precision distrubtion using mt19937.
1. `Makefile`: make file to build the code.

## Usage
Optionally takes three arguments, the mean of the distribution, the number
of random numbers to generate, and the seed for the random number
generator, e.g.,
```
$ ./generate_exp_distr 0.0 20
```
