CXX = g++
CXXFLAGS = -std=c++14 -O2 -g -Wall -Wextra
CPPFLAGS = -I/usr/include/x86_64-linux-gnu/c++/8/
LDFLAGS = -L/apps/leuven/skylake/2018a/software/icc/2018.1.163-GCC-6.4.0-2.28/tbb/lib/intel64/gcc4.7/
LDLIBS = -ltbb -lm

.PRECIOUS: %.o

all: simplest_parallel_for.exe simple_parallel_for.exe simple_parallel_reduce.exe \
     vector_parallel_reduce.exe grain_size_parallel_for.exe \
     stats_parallel_reduce.exe trivial_parallel_for.exe \
	 trivial_parallel_reduce.exe fibonacci_tasks.exe flow_graph.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) -ltbb $(LDLIBS)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
