pybind11_add_module(stats statistics_bind.cpp)
target_include_directories(stats PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../statistics)
target_link_libraries(stats PUBLIC statistics)
