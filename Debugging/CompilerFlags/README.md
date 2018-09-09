# CmopilerFlags

## What is it?
1. `BadFunctionCast`: illustrates a dangerous function call cast, caught
    by `-Wbad_function_cast`.
1. `BoundsCheck`: illustration of runtime array bounds checking for
    Fortran code.
1. `ConstQual`: illustrates bugs caused by type casts that drop the `const`
    qualifier of a variable.
1. `Conversions`: illustration of using compiler flags to detect
    suspicious data conversions.
1. `DanglingPointers`: illustration of Intel's facilities to detect
    pointer issues at runintme.
1. `FloatEqual`: illustration of the a compiler options to check for
    floating point equality/inequality comparisons.
1. `ImplicitNone`: illustrates the use of the compiler implicit none flag
    to catch type errors due to implicit typing in Fortran.
1. `IntegerOverflow`: illustrates how to use a compiler flag to trap
    integer overflow at runtime for a C application.
1. `NullPointer`: illustration of how to use GCC's sanitizer to generate
    errors on NULL pointer dereferencing.
1. `Shadow`: illustration of using the `-Wshadow` option to detect
    potential problems caused by local variable declarations that shadow
    those in outer scope.
1. `UndefMacroVar`: illustration of using the `-Wundef` option to detect
    the usage of undefined macro variables in `#if`.
1. `UninitializedVariable`: illustration of bug introduced by an
    uninitialized stack variable.
1. `UnspecifiedOrder`: illustration of bug introduced by unspecified
    execution order.
1. `UnusedVariable`: illustration of how detecting unused variables may
    help spot bugs.
