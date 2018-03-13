FC := gfortran
FFLAGS += -O2 -g -Wall -Wextra

APPS := x_prog.exe y_prog.exe

all: $(APPS)

x_OBJS = a_mod.o x.o
y_OBJS = b_mod.o y.o

x_prog.exe: $(x_OBJS)
	$(FC) $(FFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

y_prog.exe: $(y_OBJS)
	$(FC) $(FFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(FC) $(FFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.mod) $(wildcard *.exe)
	$(RM) $(wildcard core.*) core
