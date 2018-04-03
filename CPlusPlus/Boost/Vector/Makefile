CXX = g++
CXXFLAGS = -std=c++14 -O2 -g -Wall -Wextra
LDLIBS = -lm

all: boost_vector.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe) $(wildcard core.*) core
