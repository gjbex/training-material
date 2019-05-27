CXX = g++
CXXFLAGS = --std=c++14 -O2 -g -Wall -Wextra

APPS = list_stl.exe map_stl.exe set_stl.exe \
       map_functions.exe priority_queue_stl.exe \
	   vector_stl.exe

all: $(APPS)

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
