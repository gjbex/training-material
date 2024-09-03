CC = nvcc
CXX = g++
CFLAGS = -O3 -std=c++17 -g
CXXFLAGS = -O3 -std=c++11 -g -fopenmp -ftree-vectorize -march=corei7-avx

APPL = vectors.exe vectors_omp.exe

all: $(APPL)

vectors_omp.exe: vectors_omp.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

%.exe: %.cu
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o $(APPL) core.*
