CC = gcc
CFLAGS = -O1 -g -Wall -Wextra
ASMFLAGS = -S

APPL = leak.exe array_bounds.exe dangling_pointer.exe
SRCS = $(APPL:.exe=.c)
OBJS = $(SRCS:.c=.o)
ASMS = $(SRCS:.c=.s)

all: $(APPL)

asm: $(ASMS)

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $<

%.s: %.c
	$(CC) $(CFLAGS) $(ASMFLAGS) -c -o $@ $<

clean:
	$(RM) $(APPL) $(OBJS)
	$(RM) $(ASMS)
	$(RM) core core.*
