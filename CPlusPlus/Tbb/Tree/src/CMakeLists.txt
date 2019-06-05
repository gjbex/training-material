add_executable(tree_test.exe main_tree_test.cpp tree_init.cpp)
target_link_libraries(tree_test.exe -L/apps/leuven/skylake/2018a/software/icc/2018.1.163-GCC-6.4.0-2.28/tbb/lib/intel64/gcc4.7/ tbb)
