CXX = g++
CXXFLAGS = -std=c++17 -O2 -g -Wall -Wextra -Wpedantic

all: if_init.exe optional.exe structured_bindings.exe variant_visit.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
