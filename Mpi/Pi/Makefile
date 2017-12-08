MPICC ?= mpicc
CFLAGS ?= -O2 -g -Wall -Wextra
CPPFLAGS ?=
OMPFLAGS ?= -fopenmp
LDFLAGS ?=
LIBS = -lm

all: pi.exe pi_hybrid.exe

pi.exe: pi.c
	$(MPICC) $(CFLAGS) $(CPPFLAGS) -Wno-unknown-pragmas \
	         -o $@ $^ $(LDFLAGS) $(LIBS)

pi_hybrid.exe: pi.c
	$(MPICC) $(CFLAGS) $(OMPFLAGS)  $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

clean:
	rm -f *.o *.exe core
