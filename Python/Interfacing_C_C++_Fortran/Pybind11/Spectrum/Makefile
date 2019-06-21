CXX = g++
CXXFLAGS = -std=c++14 -g -O2 -Wall -Wextra -Wpedantic -fPIC
CPPFLAGS = $(shell python3 -m pybind11 --includes)
LDLIBS = -lm

PYBIND_SUFFIX = $(shell python3-config --extension-suffix)

bindings: spectrum.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -shared -o spectrum$(PYBIND_SUFFIX) $^

clean:
	$(RM) $(wildcard *.so) $(wildcard *.o)
	$(RM) core $(wildcard core.*)
