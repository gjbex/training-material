add_executable(terrain.exe terrain.cpp terrain_main.cpp)
target_include_directories(terrain.exe PRIVATE $(Boost_INCLUDE_DIR))
target_link_libraries(terrain.exe LINK_PRIVATE ${Boost_LIBRARIES})

add_executable(los_serial.exe terrain.cpp line_of_sight_serial.cpp)

add_executable(visibility_serial.exe terrain.cpp visibility_serial.cpp)

add_executable(visibility_par.exe terrain.cpp visibility_par.cpp)
target_link_libraries(visibility_par.exe tbb)
