CC = gcc
CFLAGS = -O2 -g -Wall -Wextra
OMP = -fopenmp

APPL = pi_seq.exe pi.exe pi_sse.exe

all: $(APPL)

%_seq.exe: pi.c
	$(CC) $(CFLAGS) -Wno-unknown-pragmas -o $@ $<

%.exe: %.c
	$(CC) $(CFLAGS) $(OMP) -o $@ $<

clean:
	rm -f *.o $(APPL)
