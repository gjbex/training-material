F90 = gfortran
FFLAGS = -O2 -g
LDFLAGS =
LIBS = -lm

APPL = free_source_form_test.exe cli_test.exe env_test.exe

all: $(APPL)

%.exe: %.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c $<

clean:
	rm -f $(APPL) *.o *.mod
