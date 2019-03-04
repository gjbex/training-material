CXX = g++
CXXFLAGS = --std=c++14 -Wall -Wextra -g

all: late_binding.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
