CXX = g++
CXXFLAGS = -O2 -g -Wall -std=c++11
LDLIBS = -lm

APPL = random_int.exe random_double.exe

all: $(APPL)

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

clean:
	rm -f $(APPL) *.o core
