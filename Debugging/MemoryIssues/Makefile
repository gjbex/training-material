CC = gcc
CFLAGS = -O1 -g -Wall -Wextra
ASMFLAGS = -S
LDFLAGS = -lm

APPL = leak.exe array_bounds.exe dangling_pointer.exe memory_leak.exe \
       null_pointer.exe stack_issue.exe
SRCS = $(APPL:.exe=.c)
OBJS = $(SRCS:.c=.o)
ASMS = $(SRCS:.c=.s)

all: $(APPL)

asm: $(ASMS)

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

%.s: %.c
	$(CC) $(CFLAGS) $(ASMFLAGS) -c -o $@ $<

clean:
	$(RM) $(APPL) $(OBJS)
	$(RM) $(ASMS)
	$(RM) core core.*
