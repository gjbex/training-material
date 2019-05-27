CXX = g++
CXXFLAGS = --std=c++14 -O2 -g -Wall -Wextra -Wpedantic

all: list_stl.exe map_stl.exe set_stl.exe map_functions.exe priority_queue_stl.exe \
	 vector_stl.exe valarray_stl.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
