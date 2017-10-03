CXX = g++
CXXFLAGS = -std=c++14 -O2 -g -Wall -Wextra
OMPFLAGS = -fopenmp
CPPFLAGS =
LDFLAGS =
LIBS = -lm

.PRECIOUS: %.o

all: julia_abs.exe julia.exe julia_tbb.exe julia_omp.exe \
     simple_tbb.exe simple_reduce_tbb.exe vector_reduce_tbb.exe

%_omp.exe: %_omp.cpp
	$(CXX) $(CXXFLAGS) $(OMPFLAGS) -o $@ $^ $(LIBS)

%_tbb.exe: %_tbb.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) -ltbb $(LIBS)

%.exe: %.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	$(RM) *.o *.exe
	$(RM) core core.*
