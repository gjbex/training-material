CXX = g++
CXXFLAGS = -O2 -g -Wall -std=c++14
LIBS = -lm

APPS = particles.exe fac.exe

all: $(APPS)

particles.exe: particle.o particles_main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o)
	$(RM) core $(wildcard core.)
