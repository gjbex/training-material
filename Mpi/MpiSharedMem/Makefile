CC = mpicc
CFLAGS = -O2 -g -Wall -Wextra
LIBS = -lm

all: mpi_shared_mem_c.exe ring_c.exe

%_c.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) *.o *.exe
	$(RM) core core.*
