CXX = g++
CXXFLAGS = -std=c++14 -fPIC -O3 -g -Wall -Wextra -Wpedantic
ASM = nasm
ASMFLAGS = -f elf64

all: quad_calc.exe timing.exe quad_calc_inline.exe

quad_calc.exe: quad_calc.o quad.o
	$(CXX) $(CXXFLAGS) -o $@ $^

timing.exe: timing.o quad.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $<

quad.o: quad.nsm
	$(ASM) $(ASMFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
