# ObjectOrientation

Object oriented programming in C++ may have some pitfalls, here are some
illustrations.

## What is it?

  1. `default_argument.cpp`: a derived class seem to override its base class
    virtual methods, but actually overloads one of them.  Use `override` and
    the compiler will tell you that you're not overriding.  The second
    surprise is `method3`, although the implementation in the derived class
    is used as expected, the default value of the base class is used.
    Default values are bound at compile time, while the method to call is
    determined at runtime.
  1. `member_init_order.cpp`: object attributes are initialized in the order
    they are declared in the class declaration when the constructor is
    called, regardless of the order of initialization in the constructor.
    `-Wall` will issue relevant warnings.
  1. `Makefile`: make fild to build the application.
