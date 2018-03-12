CXX = g++
CXXFLAGS = -std=c++14 -g -O2 -Wall -Wextra
LDLIBS = -lm

all: aggregate.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o)
	$(RM) $(wildcard core.*) core
