CXX = g++
CXXFLAGS = -std=c++14 -g -O2 -Wall -Wextra
CPPFLAGS = -MMD -MP
LIBS = -lm

all: quad.exe

quad.exe: simpson_quad.o gaussian_quad.o main_quad.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(wildcard *.d)

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o) $(wildcard *>d)
	$(RM) core $(wildcard core.*)
