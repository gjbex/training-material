CXX = g++
CXXFLAGS = -std=c++14 -g -O2 -Wall -Wextra
CPPFLAGS = -MMD -MP

all: rng_runner.exe

rng_runner.exe: rng.o rng_builder.o rng_runner.o
	$(CXX) $(CXXFLAGS) -o $@ $^

-include $(wildcard *.d)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe) $(wildcard *.d)
	$(RM) core $(wildcard core.*)
