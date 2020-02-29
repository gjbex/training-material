cmake_minimum_required(VERSION 3.0)

project(fac_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

add_compile_options(-Wall -Wextra -Wpedantic -g)

add_executable(fac.exe fac.cpp)

enable_testing()

add_test(
    NAME Runs
    COMMAND ./fac.exe 0
)
add_test(
    NAME NoArgs
    COMMAND ./fac.exe
)
set_tests_properties(NoArgs
    PROPERTIES WILL_FAIL TRUE
)
add_test(
    NAME Value0
    COMMAND ./fac.exe 0
)
set_tests_properties(Value0
    PROPERTIES PASS_REGULAR_EXPRESSION "1"
)
add_test(
    NAME Value3
    COMMAND ./fac.exe 3
)
set_tests_properties(Value3
    PROPERTIES PASS_REGULAR_EXPRESSION "6"
)
add_test(
    NAME NegValue
    COMMAND ./fac.exe -1
)
set_tests_properties(NegValue
    PROPERTIES WILL_FAIL TRUE
)
