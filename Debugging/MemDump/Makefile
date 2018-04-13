CC = gcc
CFLAGS = -g
CPPFLAGS = -MMD -MP
LDLIBS = -lm

all: arrays.exe

%.exe: %.o
	$(CC) -o $@ $< $(LDLIBS)

-include $(wildcard *.d)
clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe) $(wildcard *.d)
	$(RM) $(wildcard core.*) core
