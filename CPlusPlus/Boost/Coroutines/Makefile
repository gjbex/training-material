CXX = g++
CXXFLAGS = --std=c++14 -g -O2 -Wall -Wextra
LDFLAGS = -L$(BOOST_ROOT)/lib
LDLIBS = -lboost_coroutine -lboost_context

all: range.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
