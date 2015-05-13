F90 = gfortran
FFLAGS = -g2 -O2
LDFLAGS = 
LIBS =

OBJS = linked_list_mod.o list_test.o

all: list_test.exe

list_test.exe: $(OBJS)
	$(F90) $(FFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c -o $@ $<

clean:
	rm -f *.mod *.o *.exe
