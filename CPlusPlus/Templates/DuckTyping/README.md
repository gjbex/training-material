# DuckTyping
Example of using a template for duck typing.

## What is it?
1. `simpson_quad.h`: class that implements Simpson quadrature.
1. `simpson_quad.cpp`: implementation of `SimpsonQuad` methods.
1. `gaussian_quad.h`: class that implementation Gaussian quadrature.
1. `gaussian_quad.cpp`: implementation of `GaussianQuad` methods.
1. `main_quad.cpp`: main function that drives the quadrature using an
    algorithm determined at runtime, either based on `SimpsonQuad`, or
    `GaussianQuad`.
1. `Makefile`: make file to build the application.
