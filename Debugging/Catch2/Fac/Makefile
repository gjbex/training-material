CXX = g++
CXXFLAGS = -std=c++14 -g -O2 -Wall -Wextra
CPPFLAGS = $(shell pkg-config catch --cflags)

all: test_fac.exe

test_fac.exe: fac.o test_fac.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
