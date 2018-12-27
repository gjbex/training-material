CXX = g++
CXXFLAGS = -std=c++14 -g -O2 -Wall -Wextra
LDLIBS = -lm

all: fac.exe memory_leak.exe memory_leak_fixed.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o)
	$(RM) core $(wildcard core.)
