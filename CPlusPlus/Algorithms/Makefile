CXX = g++
CXXFLAGS = -O2 -g -std=c++14 -Wall
LIBS = -lm


APPS = permutations.exe generate.exe for_each.exe

all: $(APPS)

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PRECIOUS: %.o

clean:
	rm -f $(APPS) *.o *.gch
