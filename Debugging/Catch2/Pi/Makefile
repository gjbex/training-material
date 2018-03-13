CXX = g++
CXXFLAGS = -std=c++14 -g -O2 -Wall -Wextra
CPPFLAGS = $(shell pkg-config catch --cflags)

all: test_pi.exe

checks: test_pi.exe
	./$^

test_pi.exe: pi.o test_pi.o test_main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
