CXX = g++
CXXFLAGS = -std=c++14 -g -O2 -Wall -Wextra
# CPPFLAGS = -I/usr/local/software/boost/1.66.0/include
# LDFLAGS = -L/usr/local/software/boost/1.66.0/lib
LDLIBS = -lboost_program_options

all: random.exe

.PRECIOUS: %.o

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) $(wildcard core.*) core
