# build shared library
add_library(stats SHARED stats.cpp table_stats.cpp)

# set the public header files
set_target_properties(stats PROPERTIES PUBLIC_HEADER "stats.h;table_stats.h")

# installation directives
install(TARGETS stats
        LIBRARY
          DESTINATION lib
          COMPONENT runtime
        PUBLIC_HEADER
          DESTINATION include
          COMPONENT development
       )
