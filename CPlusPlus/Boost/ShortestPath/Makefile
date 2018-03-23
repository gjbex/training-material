CXX = g++
CXXFLAGS = -std=c++14 -g -O2 -Wall -Wextra
# adapt if Boost is not in standard location
CPPFLAGS =

all: shortest_path.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
