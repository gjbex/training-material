CXX = g++
CXXFLAGS = -std=c++14 -g -O2 -Wall -Wextra
CPPFLAGS = -I/usr/local/software/catch2/2.5.0/single_include

all: test_fac.exe

checks: test_fac.exe
	./$^

test_fac.exe: fac.o test_fac.o test_main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
