add_executable(greetings greetings.c)
target_include_directories(greetings PUBLIC Funcs)
target_link_libraries(greetings funcs)

add_subdirectory(Funcs)

install(TARGETS greetings
    RUNTIME
        DESTINATION bin
        COMPONENT runtime
)
