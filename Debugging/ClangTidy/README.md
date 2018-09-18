# CppCheck
Illustrations of problems to try and find using `clang-tidy`.

## What is it?
1. `addition.c`: scope of variable can be reduced.
1. `array.c`: illustration of three bugs.
1. `array.cpp`: illustration of three bugs.
1. `array_bounds.c`: format string mismatch with `printf` arguments.
1. `logical_order.c`: possible null pointer dereference.
1. `memory_leak.c`: memory leak.
1. `stack_issue.c`: returning data from a function that is on the stack.
1. `uninitialized_variable.c`: using a variable that is not initialized.
1. `minimum.cpp`: reassigning a variable before the value is being used;
    consecutive return statements.
1. `priority_queue_stl.cpp`: class member function can be constant;
    function parameter should be passed by reference (performance).
1. `rpn_calc.cpp`: exception should be caught by reference.
1. `serialization.cpp`: variable is assigned a value that is never used.
1. `CMakeLists.txt`: CMake file to build the applications.
1. `setup_compilation_database.sh`: script to generate the compilation
    database.
1. `setup_config_file.sh`: script to create the `clang-tidy` 
    configuration file.
