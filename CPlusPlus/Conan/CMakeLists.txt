cmake_minimum_required(VERSION 3.0)
project(args_test LANGUAGES CXX)

set(CMAKE_CXX_COMPILER  g++)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(generate_gaussian.exe generate_gaussian.cpp)
target_link_libraries(generate_gaussian.exe ${CONAN_LIBS})
