# specify CMake version to use
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# specify the name of the project, and the programming language(s)
project(statistics LANGUAGES CXX)

# set version information
set(statistics_NAME statistics)
set(statistics_VERSION_MAJOR 1)
set(statistics_VERSION_MINOR 0)

# add source directory
add_subdirectory(src)
