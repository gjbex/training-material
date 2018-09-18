cmake_minimum_required(VERSION 3.10)

add_executable (addition.exe addition.c)
install (TARGETS addition.exe DESTINATION bin)

add_executable (array_bounds.exe array_bounds.c)
install (TARGETS array_bounds.exe DESTINATION bin)

add_executable (array.exe array.c)
install (TARGETS array.exe DESTINATION bin)

add_executable (logical_operators.exe logical_operators.c)
install (TARGETS logical_operators.exe DESTINATION bin)

add_executable (logical_order.exe logical_order.c)
install (TARGETS logical_order.exe DESTINATION bin)

add_executable (memory_leak.exe memory_leak.c)
install (TARGETS memory_leak.exe DESTINATION bin)

add_executable (stack_issue.exe stack_issue.c)
install (TARGETS stack_issue.exe DESTINATION bin)

add_executable (uninitialized_variable.exe uninitialized_variable.c)
install (TARGETS uninitialized_variable.exe DESTINATION bin)
