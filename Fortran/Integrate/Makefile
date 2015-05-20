F90 = gfortran
FFLAGS = -O2 -g
LDFLAGS =
LIBS =

INT_OBJS = quad_func_interface.o quad_mod.o simpson_mod.o gauss_mod.o \
           integration_test.o

all: integration_test.exe

integration_test.exe: $(INT_OBJS)
	$(F90) $(FFLAGS) -o $@ $(INT_OBJS) $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c -o $@ $<

clean:
	rm -f *.exe *.o *.mod core
