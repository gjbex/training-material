CC = gcc
CFLAGS = -g -Wall -Wextra -O2
CXX = g++
CXXFLAGS = -g -Wall -Wextra -O2
LDLIBS = -lm

all: valgrind.exe local_leak.exe

check_valgrind: valgrind.exe
	valgrind --leak-check=full ./$<

check_local_leak: local_leak.exe
	valgrind --leak-check=full ./$<

valgrind.exe: valgrind.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

local_leak.exe: local_leak.c
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

sanitize: local_leak.exe
	$(CC) $(CFLAGS) -fsanitize=leak -o $< local_leak.c $(LDLIBS)
	./$<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
