FC = mpif90
FFLAGS = -O2 -g -Wall -Wextra

all: deadlock.exe async_send.exe data_race.exe async_recv.exe \
	 async_test.exe

%.exe: %.o
	$(FC) $(FFLAGS) -o $@ $<

%.o: %.f90
	$(FC) $(FFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.mod) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
