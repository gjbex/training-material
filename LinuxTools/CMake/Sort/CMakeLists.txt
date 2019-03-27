# minimum CMake version
cmake_minimum_required(VERSION 3.12)

# project name and language settings
project(sorting LANGUAGES CXX)

# set C++ standard requirements
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# find the Catch2 unit testing library
find_package(Catch2 REQUIRED)

# add executable and link library for Catch2
add_executable(tdd_sort.exe tdd_sort.cpp)
target_link_libraries(tdd_sort.exe Catch2::Catch2)
