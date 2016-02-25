F90 = gfortran
FFLAGS = -O2 -g
LDFLAGS =
LIBS =

APPS = x_prog.exe y_prog.exe

all: $(APPS)

x_OBJS = a_mod.o x.o
y_OBJS = b_mod.o y.o

x_prog.exe: $(x_OBJS)
	$(F90) $(FFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

y_prog.exe: $(y_OBJS)
	$(F90) $(FFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.mod $(APPS)
