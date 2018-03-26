CXX = g++
CXXFLAGS = -g

all: valgrind.exe

checks: valgrind.exe
	valgrind --leak-check=full ./$<

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
