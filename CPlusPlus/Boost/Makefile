CXX = g++
CXXFLAGS = -O2 -g -Wall -std=c++14
LDLIBS = -lm

.PRECIOUS: %.o

APPS = lorenz.exe boost_vector.exe

all: $(APPS)

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(APPS) *.o
