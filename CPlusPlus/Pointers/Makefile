CXX = g++
CXXFLAGS = -std=c++14 -Wall -O2 -g

.PRECIOUS: *.o

all: tree.exe tree_sptr.exe

tree.exe: tree.o
	$(CXX) $(CXXFLAGS) -o $@ $^

tree_sptr.exe: tree_sptr.o
	$(CXX) $(CXXFLAGS) -o $@ $^

tree.o: tree.cpp node.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tree_sptr.o: tree_sptr.cpp node_sptr.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.exe
