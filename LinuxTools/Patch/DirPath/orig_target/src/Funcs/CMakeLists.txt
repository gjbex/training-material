add_library(funcs SHARED funcs.c)
set_target_properties(funcs PROPERTIES PUBLIC_HEADER "funcs.h")

install(TARGETS funcs
    LIBRARY
        DESTINATION lib
        COMPONENT runtime
    PUBLIC_HEADER
        DESTINATION include
        COMPONENT development
)
