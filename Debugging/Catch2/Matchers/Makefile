CXX = g++
CXXFLAGS = -std=c++14 -g -O2 -Wall -Wextra
CPPFLAGS = -I/usr/local/software/catch2/2.5.0/single_include

all: ip_address.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
