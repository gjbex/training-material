CXX = g++
CXXFLAGS = -std=c++14 -O2 -g -Wall -Wextra
CPPFLAGS = $(shell pkg-config --cflags gsl)
LDFLAGS = $(shell pkg-config --libs gsl)

all: cannon_max_range.exe minimum.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	$(RM) *.exe *.o
	$(RM) core core.*
