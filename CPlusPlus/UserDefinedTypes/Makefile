CXX = g++
CXXFLAGS = -std=c++14 -O2 -g -Wall -Wextra
LDLIBS = -lm

all: struct_particles.exe class_particles.exe charged_particles.exe \
     streaming_stats.exe function_objects.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o)
	$(RM) core $(wildcard core.*)
