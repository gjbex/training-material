CXX = g++
CXXFLAGS = -std=c++14 -O2 -g -Wall -Wextra
LIBS = -lm

APPS = struct_particles.exe class_particles.exe charged_particles.exe \
       stats_compute.exe

all: $(APPS)

stats_compute.exe: stats_compute.o stats.o stats.h
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(APPS) *.o
