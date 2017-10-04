# CmopilerFlags

## What is it?
1. `ConstQual`: illustrates bugs caused by type casts that drop the `const`
    qualifier of a variable.
1. `Shadow`: illustration of using the `-Wshadow` option to detect
    potential problems caused by local variable declarations that shadow
    those in outer scope.
1. `UninitializedVariable`: illustration of bug introduced by an
    uninitialized stack variable.
1. `UnspecifiedOrder`: illustration of bug introduced by unspecified
    execution order.
