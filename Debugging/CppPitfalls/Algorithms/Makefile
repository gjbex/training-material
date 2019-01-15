CXX = g++
CXXFLAGS = -g -O2 -std=c++14 -Wall -Wextra

all: accumulate.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o)
	$(RM) core $(wildcard core.*)
