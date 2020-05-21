cmake_minimum_required(VERSION 3.0)

project(Nqueens LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

add_compile_options(-Wall -Wextra -Wpedantic)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy" DOC "Path to clang-tidy executable")
if(NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy not found.")
else()
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=read**,perf*,bug*,clang*,modern*")
endif()

add_executable(nqueens.exe
    nqueens.cpp
    state.cpp
)

if(CLANG_TIDY_EXE)
    set_target_properties(nqueens.exe
        PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif()
