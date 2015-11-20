MPICC = mpiicc
CFLAGS = -O2 -g
CPPFLAGS =
LDFLAGS = -mt_mpi
LIBS =

all: nonblocking_reduce.exe

%.exe: %.c
	$(MPICC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

clean:
	rm -f *.exe .o
