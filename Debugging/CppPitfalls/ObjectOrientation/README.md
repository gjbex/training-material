# ObjectOrientation

Object oriented programming in C++ may have some pitfalls, here are some
illustrations.

## What is it?

  1. `default_argument.cpp`: a derived class seem to override its base class
    virtual methods, but actually overloads one of them.  Use `override` and
    the compiler will tell you that you're not overriding.
  1. `member_init_order.cpp`: object attributes are initialized in the order
    they are declared in the class declaration when the constructor is
    called, regardless of the order of initialization in the constructor.
    `-Wall` will issue relevant warnings.
  1. `Makefile`: make fild to build the application.
