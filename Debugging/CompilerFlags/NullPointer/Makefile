CC = gcc
CFLAGS = -g -O2 -Wall -Wextra

segfault: null_pointer.exe

error_msg: null_pointer.exe

error_msg: CFLAGS += -fsanitize=undefined

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o)
	$(RM) $(wildcard core.*) core
