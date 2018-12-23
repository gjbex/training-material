CXX = g++
CXXFLAGS = -fopenmp -std=c++14 -O2 -g -Wall -Wextra
LDLIBS = -lm

all: julia_omp.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o)
	$(RM) core $(wildcard core.*)
