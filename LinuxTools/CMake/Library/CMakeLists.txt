# specify CMake version to use
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# specify the name of the project, and the programming language(s)
project(statistics LANGUAGES CXX)

# set C++ standard requirements
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# add source directory
add_subdirectory(src)
