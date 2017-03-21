CXX = g++
CXXFLAGS = -O2 -g -Wall -std=c++14
LIBS = -lm

.PRECIOUS: %.o

APPL = swap.exe

all: $(APPL)

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(APPL)
