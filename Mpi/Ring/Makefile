FCC = mpifort
CC = mpicc
FFLAGS = -Wall -O2 -g
CFLAGS = -Wall -O2 -g
LDFLAGS =
LDLIBS = -lm

all: unidirectional.exe nonblocking.exe deadlock.exe bidirectional.exe \
     sendrecv.exe cart_sendrecv.exe torus.exe one_sided.exe \
	 bidirectional_request_array.exe nonblocking_f08.exe

f08: nonblocking_f08.exe cart_sendrecv_f08.exe

bidirectional_request_array.exe: bidirectional_request_array.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LDLIBS)

%.exe: %.o
	$(FCC) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LDLIBS)

%.o: %.f90
	$(FCC) $(FFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.mod) $(wildcard *.exe) core
