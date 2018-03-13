CXX = g++
CXXFLAGS = -std=c++14 -g -O2 -Wall -Wextra -fPIC
CPPFLAGS = $(shell pkg-config catch --cflags)
LDFLAGS = -L.
LDLIBS = -lfac

all: fac.exe

checks: test_fac.exe
	./$^

libfac.so: fac.o
	$(CXX) $(CXXFLAGS) -shared -o $@ $< $(LDFLAGS)

fac.exe: libfac.so fac_main.o
	$(CXX) $(CXXFLAGS) -o $@ fac_main.o $(LDFLAGS) $(LDLIBS)

test_fac.exe: libfac.so test_fac.o test_main.o
	$(CXX) $(CXXFLAGS) -o $@ test_fac.o test_main.o $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe) $(wildcard *.so)
