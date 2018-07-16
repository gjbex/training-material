CXX = g++
CXXFLAGS = -O2 -g -std=c++14 -Wall -Wextra
LDLIBS = -lm

.PRECIOUS = %.o

APPS = find_if.exe permutations.exe generate.exe for_each.exe \
       particle_sort.exe count_clamp.exe find_words.exe zip_it.exe \
       accumulate.exe distance.exe iota.exe

all: $(APPS)

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PRECIOUS: %.o

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o) $(wildcard *.gch)
	$(RM) $(wildcard core.*) core
