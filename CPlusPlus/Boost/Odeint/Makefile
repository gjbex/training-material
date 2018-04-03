CXX = g++
CXXFLAGS = -std=c++14 -O2 -g -Wall -Wextra
LDLIBS = -lm

APPS = lorenz.exe

all: lorenz.exe

plot: lorenz.exe lorenz.txt
	./plot_lorenz.plt

lorenz.txt: lorenz.exe
	./$< > $@

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o)
	$(RM) lorenz.txt
	$(RM) $(wildcard core.*) core
