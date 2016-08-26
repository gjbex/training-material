CXX = g++
CXXFLAGS = -O2 -g -Wall -std=c++11

APPL = family_tree.exe

all: $(APPL)

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(APPL) *.o core
