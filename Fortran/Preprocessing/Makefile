F90 = ifort
FFLAGS = -g -O2 -Wall -cpp
override BYE +=

all: preprocessing.exe

%.exe: %.o
	$(F90) $(FFLAGS) -o $@ $^

%.o: %.f90
	$(F90) $(FFLAGS) $(BYE) -c -o $@ $^

clean:
	rm -f preprocessing.exe core *.o *.mod
