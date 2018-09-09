CC = gcc
FC = gfortran
CFLAGS = -O1 -g -Wall -Wextra
FFLAGS = -O1 -g -Wall -Wextra
ASMFLAGS = -S
LDLIBS = -lm

APPL = leak.exe array_bounds.exe dangling_pointer.exe memory_leak.exe \
       null_pointer.exe stack_issue.exe stack_overflow_f90.exe \
       bad_access_f90.exe deallocating_f90.exe free.exe \
       trivial_array_bounds.exe unallocated_f90.exe

SRCS = $(filter-out %_f90.c, $(APPL:.exe=.c))
OBJS = $(SRCS:.c=.o)
ASMS = $(SRCS:.c=.s)
CHECKS = $(SRCS)

all: $(APPL)

asm: $(ASMS)

%_f90.exe: %.f90
	$(FC) $(FFLAGS) -o $@ $< $(LDLIBS)

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

%.s: %.c
	$(CC) $(CFLAGS) $(ASMFLAGS) -c -o $@ $<

check: $(CHECKS)
	cppcheck --quiet --enable=all --inconclusive \
             --language=c --std=c89 --platform=unix64 $^

clean:
	$(RM) $(APPL) $(OBJS)
	$(RM) $(ASMS)
	$(RM) $(wildcard *.mod)
	$(RM) core $(wildcard core.*) $(wildcard vgcore.*)
