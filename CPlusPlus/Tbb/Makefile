CXX = g++
CXXFLAGS = -O2 -g -Wall -std=c++14
CPPFLAGS =
LDFLAGS =
LIBS = -lm

.PRECIOUS: %.o

all: julia_abs.exe julia.exe julia_tbb.exe julia_omp.exe \
     simple_tbb.exe simple_reduce_tbb.exe vector_reduce_tbb.exe

%_omp.exe: %_omp.cpp
	$(CXX) $(CXXFLAGS) -fopenmp -o $@ $^ $(LIBS)

%_tbb.exe: %_tbb.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) -ltbb $(LIBS)

%.exe: %.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.exe
