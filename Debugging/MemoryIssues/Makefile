CC = gcc
FC = gfortran
CFLAGS = -O1 -g -Wall -Wextra
FFLAGS = -O1 -g -Wall -Wextra
ASMFLAGS = -S
LDFLAGS = -lm

APPL = leak.exe array_bounds.exe dangling_pointer.exe memory_leak.exe \
       null_pointer.exe stack_issue.exe stack_overflow_f90.exe
SRCS = $(APPL:.exe=.c)
OBJS = $(SRCS:.c=.o)
ASMS = $(SRCS:.c=.s)

all: $(APPL)

asm: $(ASMS)

%_f90.exe: %.f90
	$(FC) $(FFLAGS) -o $@ $< $(LDFLAGS)

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

%.s: %.c
	$(CC) $(CFLAGS) $(ASMFLAGS) -c -o $@ $<

clean:
	$(RM) $(APPL) $(OBJS)
	$(RM) $(ASMS)
	$(RM) *.mod
	$(RM) core core.*
