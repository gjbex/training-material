# set minimal version for CMake
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# project name and specifications
project(minimum LANGUAGES CXX)

# C++ compiler and C++ standard to use
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# this project depends on GSL, find it.  Libraries will be in GSL::gsl and
# GSL::gslcblas
find_package(GSL REQUIRED)
if (NOT GSL_FOUND)
    message(FATAL_ERROR "GSL is required, but not found")
endif (NOT GSL_FOUND)

# add src subdirectory
add_subdirectory(src)
