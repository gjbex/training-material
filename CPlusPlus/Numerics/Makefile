CXX = g++
CXXFLAGS = -O2 -g -std=c++14 -Wall
LDLIBS = -lm

.PRECIOUS: %.o

APPL = complex.exe limits.exe julia.exe random.exe multiple_distr.exe

all: $(APPL)

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(APPL)
