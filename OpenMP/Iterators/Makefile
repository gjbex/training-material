CXX = g++
CXXFLAGS = -fopenmp -O2 -g -Wall -Wextra

all: vector_index.exe vector_iterator.exe

vector_index.exe: vector.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

vector_iterator.exe: vector.cpp
	$(CXX) $(CXXFLAGS) -DITERATOR -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
