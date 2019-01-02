CXX = g++
CXXFLAGS = -std=c++14 -g -O2 -Wall -Wextra -Wpedantic
ASM = nasm
ASMFLAGS = -f elf64

all: calc_sum.exe timing.exe timing_compiler.exe

timing.exe: timing.o calc_sum_function.o
	$(CXX) $(CXXFLAGS) -o $@ $^

timing_compiler.exe: timing.o calc_sum_function_compiler.o
	$(CXX) $(CXXFLAGS) -o $@ $^

calc_sum.exe: calc_sum.o calc_sum_function.o
	$(CXX) $(CXXFLAGS) -o $@ $^

calc_sum_function.o: calc_sum_function.nsm
	$(ASM) $(ASMFLAGS) -o $@ $<

calc_sum_function_compiler.o: calc_sum_function_compiler.nsm
	$(ASM) $(ASMFLAGS) -o $@ $<

# calc_sum.o: calc_sum.cpp
# 	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
