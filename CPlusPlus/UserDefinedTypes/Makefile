CXX = g++
CXXFLAGS = -O2 -g -Wall -std=c++14
LIBS = -lm

APPS = struct_particles.exe class_particles.exe

all: $(APPS)

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(APPS) *.o
