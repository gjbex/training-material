CXX = g++
CXXFLAGS = -O2 -g -Wall -std=c++14
LIBS = -lm

APPL = particles.exe

all: $(APPL)

particles.exe: main.o particle.o static_particle.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(APPL) *.o *.gch
