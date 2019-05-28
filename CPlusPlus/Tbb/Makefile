CXX = g++
CXXFLAGS = -std=c++14 -O2 -g -Wall -Wextra
CPPFLAGS = -I/usr/include/x86_64-linux-gnu/c++/8/
LDFLAGS =
LDLIBS = -lm

.PRECIOUS: %.o

all: simplest_tbb.exe simple_tbb.exe simple_reduce_tbb.exe vector_reduce_tbb.exe \
        grain_size_tbb.exe auto_partitioner_tbb.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) -ltbb $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	$(RM) *.o *.exe
	$(RM) core core.*
