CXX = g++
CXXFLAGS = -std=c++14 -O2 -g -Wall -Wextra
CPPFLAGS = -MMD -MP
LDLIBS = -lm

all: gadget.exe

gadget.exe: main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(wildcard *.d)

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o) $(wildcard *.d)
	$(RM) core $(wildcard core.*)
