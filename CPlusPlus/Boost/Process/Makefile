CXX = g++
# warning switched off to avoid warnings on Boost header file
CXXFLAGS = -std=c++14 -g -O2 -Wall -Wno-unused-result
LDLIBS = -lboost_filesystem -lboost_system -lpthread

all: ls.exe bc.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDLIBS)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) $(wildcard core.*) core
