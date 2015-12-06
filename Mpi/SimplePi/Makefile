MPICC = mpicc
CFLAGS = -O2 -g
CPPFLAGS =
LDFLAGS =
LIBS =

all: pi.exe

%.exe: %.o
	$(MPICC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.c
	$(MPICC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -f *.o *.exe core
