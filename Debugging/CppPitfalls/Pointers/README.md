# Pointers

Pointers and references can have some interesting properties and differences.

## What is it?

  1. `pointers_vs_references.cpp`: a different address can be reassigned to
    a C++ pointer.  However, a reference always refers to the same object.
  1. `temporary_objects.cpp`: a `static_cast` of an objct will construct a
    new object using the copy constructor, hence abusing `static_cast` to
    call parent methods on a derived class object is not going to work.
  1. `Makefile`: make file to build the applicatons.
