CC = mpicc
CFLAGS = -O2 -g
LIBS = -lm

all: mpi_shared_mem_c.exe

%_c.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) *.o *.exe
	$(RM) core core.*
