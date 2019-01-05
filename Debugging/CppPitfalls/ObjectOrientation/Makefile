CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Wextra

all: default_argument.exe member_init_order.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
