CXX = g++
CXXFLAGS = -O2 -g -Wall -std=c++14
LIBS = -lm

.PRECIOUS: %.o

APPS = lorenz.exe boost_vector.exe

all: $(APPS)

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(APPS) *.o
