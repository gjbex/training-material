CXX = g++
CXXFLAGS = -std=c++14 -O2 -g -Wall -Wextra
CPPFLAGS = -I/usr/include/x86_64-linux-gnu/c++/8/
LDFLAGS = -L/apps/leuven/skylake/2018a/software/icc/2018.1.163-GCC-6.4.0-2.28/tbb/lib/intel64/gcc4.7/
LDLIBS = -ltbb -lm

.PRECIOUS: %.o

all: simplest_tbb.exe simple_tbb.exe simple_reduce_tbb.exe \
     vector_reduce_tbb.exe grain_size_tbb.exe \
     auto_partitioner_tbb.exe stats_tbb.exe trivial_for.exe \
     trivial_reduce.exe fibonacci_tasks.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) -ltbb $(LDLIBS)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
