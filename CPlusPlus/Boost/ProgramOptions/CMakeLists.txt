cmake_minimum_required(VERSION 3.0)
project(ProgramOptions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSION NO)

add_compile_options(-Wall -Wextra -Wpedantic)

find_package(Boost COMPONENTS program_options)
if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost is required but can't be found")
endif (NOT Boost_FOUND)

add_executable(random.exe random.cpp)
target_include_directories(random.exe PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries(random.exe LINK_PRIVATE ${Boost_LIBRARIES})

add_executable(random_default.exe random_default.cpp)
target_include_directories(random_default.exe PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries(random_default.exe LINK_PRIVATE ${Boost_LIBRARIES})
