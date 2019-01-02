F90 ?= gfortran
FFLAGS ?= -O2 -g -Wall -Wextra -Wuninitialized
LDFLAGS ?=
LIBS ?=

INT_OBJS = quad_func_interface.o quad_mod.o simpson_mod.o gauss_mod.o \
           integration_test.o
XW_OBJS = quad_func_interface.o quad_mod.o gauss_mod.o xw_test.o

GAUSS_OBJS = quad_func_interface.o quad_mod.o gauss_mod.o gauss_test.o

all: integration_test.exe xw_test.exe gauss_test.exe

integration_test.exe: $(INT_OBJS)
	$(F90) $(FFLAGS) -o $@ $(INT_OBJS) $(LDFLAGS) $(LIBS)

xw_test.exe: $(XW_OBJS)
	$(F90) $(FFLAGS) -o $@ $(XW_OBJS) $(LDFLAGS) $(LIBS)

gauss_test.exe: $(GAUSS_OBJS)
	$(F90) $(FFLAGS) -o $@ $(GAUSS_OBJS) $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c -o $@ $<

clean:
	rm -f *.exe *.o *.mod core
