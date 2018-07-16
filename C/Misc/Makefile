CC = gcc
CFLAGS = -O2 -g -Wall -Wextra

all: const_int_ptr_vs_int_const_ptr.exe

errors: const_int_ptr_vs_int_const_ptr.c
	$(CC) $(CFLAGS) -DCOMPILE_ERROR -c $<

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) $(wildcard core.*) core
