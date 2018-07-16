# Quadrature
Example of a class hierarchy with an abstract base class.

## What is it?
1. `quad.h`: abstract base class that defines a virtual method.
1. `simpson_quad.h`: derived class from `Quad` that overrides the virtual
    method.
1. `simpson_quad.cpp`: implementation of `SimpsonQuad` methods.
1. `gaussian_quad.h`: derived class from `Quad` that overrides the virtual
    method.
1. `gaussian_quad.cpp`: implementation of `GaussianQuad` methods.
1. `main_quad.cpp`: main function that drives the quadrature using an
    algorithm determined at runtime, either based on `SimpsonQuad`, or
    `GaussianQuad`.
1. `Makefile`: make file to build the application.
