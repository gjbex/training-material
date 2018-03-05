CXX = g++
CXXFLAGS = -std=c++14 -O2 -g -Wall -Wextra
LIBS = -lm

all: struct_particles.exe class_particles.exe charged_particles.exe \
     streaming_stats.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o)
	$(RM) core $(wildcard core.*)
