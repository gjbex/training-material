# add executable:w
add_executable(stats.exe stats_main.cpp)
# add include directory for header files
target_include_directories(stats.exe PUBLIC stats)
# add libraries to link executable with
target_link_libraries(stats.exe stats)

# add executable:w
add_executable(table_stats.exe stats_main.cpp)
# add include directory for header files
target_include_directories(table_stats.exe PUBLIC stats)
# add libraries to link executable with
target_link_libraries(table_stats.exe stats)

# add directory with library code
add_subdirectory(stats)

# installation directives
install(TARGETS stats.exe table_stats.exe
        RUNTIME
          DESTINATION bin
          COMPONENT runtime
       )
