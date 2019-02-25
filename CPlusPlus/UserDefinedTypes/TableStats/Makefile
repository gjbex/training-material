CXX = g++
CPPFLAGS = -MMD -MP
CXXFLAGS = -std=c++14 -g -O2 -Wall -Wextra

all: stats.exe table_stats.exe

stats.exe: stats.o stats_main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

table_stats.exe: stats.o table_stats.o table_stats_main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

-include $(wildcard *.d)

clean:
	$(RM) $(wildcard *.d) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
