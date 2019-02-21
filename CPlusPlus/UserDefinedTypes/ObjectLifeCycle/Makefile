CXX = g++
CXXFLAGS = -std=c++17 -O2 -g -Wall -Wextra
CPPFLAGS = -MMD -MP
LDLIBS = -lm

all: gadget.exe emplace.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

-include $(wildcard *.d)

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o) $(wildcard *.d)
	$(RM) core $(wildcard core.*)
