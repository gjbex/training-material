CXX = g++
CPPFLAGS = -MMD -MP
CXXFLAGS = -std=c++14 -Wall -Wextra -Wnon-virtual-dtor

all: CXXFLAGS += -O2
all: stats.exe

debug: CXXFLAGS += -O0 -g
debug: all

stats.exe: stats.o median_stats.o stats_main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

-include $(wildcard *.d)

clean:
	$(RM) $(wildcard *.d) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
