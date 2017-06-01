CXX = g++
CXXFLAGS = -std=c++14 -Wall -O2 -g

.PRECIOUS: *.o

all: tree.exe

tree.exe: tree.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp node.h node.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.exe
