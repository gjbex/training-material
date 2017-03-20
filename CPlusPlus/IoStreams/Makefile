CXX = g++
CXXFLAGS = -O2 -g -std=c++14 -Wall
LIBS = -lm

.PRECIOUS: %.o

APPL = sum.exe

all: $(APPL)

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(APPL)
