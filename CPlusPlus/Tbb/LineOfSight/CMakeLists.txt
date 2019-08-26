cmake_minimum_required(VERSION 3.0)
project(line_of_sight LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

add_compile_options(-Wall -Wextra -Wpedantic)

add_subdirectory(src)
