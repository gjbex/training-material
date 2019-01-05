CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Wextra

all: pointers_vs_references.exe temporary_object.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
