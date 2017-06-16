CXX = g++
CXXFLAGS = -std=c++14 -Wall -O2 -g

.PRECIOUS: *.o

all: tree.exe tree_sptr.exe tree_uptr.exe

tree.exe: tree.o
	$(CXX) $(CXXFLAGS) -o $@ $^

tree_sptr.exe: tree_sptr.o
	$(CXX) $(CXXFLAGS) -o $@ $^

tree_uptr.exe: tree_uptr.o
	$(CXX) $(CXXFLAGS) -o $@ $^

tree.o: tree.cpp node.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tree_sptr.o: tree_sptr.cpp node_sptr.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tree_uptr.o: tree_uptr.cpp node_uptr.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.exe
