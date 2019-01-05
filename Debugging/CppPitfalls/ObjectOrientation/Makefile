CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Wextra

all: default_argument.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
