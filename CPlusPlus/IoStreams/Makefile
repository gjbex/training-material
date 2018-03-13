CXX = g++
CXXFLAGS = -std=c++14 -O2 -g -Wall -Wextra
LDLIBS = -lm

all: csv2tsv.exe formatting.exe serialization.exe sum.exe \
     aggregate.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) $(wildcard core.*) core
