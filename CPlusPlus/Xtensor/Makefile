CXX = g++
CXXFLAGS = -std=c++14 -O2 -Wall -Wextra
CPPFLAGS = -I/usr/local/software/xtl/0.5.1/include \
		   -I/usr/local/software/xtensor/0.19.1/include
LDLIBS = -lm

all: elementwise.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $< $(LDLIBS)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
