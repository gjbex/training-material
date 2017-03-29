CXX = g++
CXXFLAGS = -O2 -g -Wall -std=c++14
CPPFLAGS =
LDFLAGS =
LIBS = -lm

.PRECIOUS: %.o

all: julia.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.exe
