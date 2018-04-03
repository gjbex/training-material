CXX = g++
CXXFLAGS = -std=c++14 -g -O2 -Wall -Wextra

all: units_okay.exe

not_okay: units_not_okay.o

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $<

units_not_okay.o: units_not_okay.cpp
	-$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o)
	$(RM) $(wildcard core.*) core
