CC = gcc
CFLAGS = -g -Wall -Wextra -O2

all: allocation_error.exe command_line_args_error.exe file_error.exe \
	 read_error.exe read_error_incorrect.exe

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) $(wildcard core.*) core
