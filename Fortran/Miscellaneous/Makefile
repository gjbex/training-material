F90 = gfortran
FFLAGS = -O2 -g
LDFLAGS =
LIBS = -lm

APPL = free_source_form_test

all: $(APPL)

free_source_form_test: free_source_form_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c $<

clean:
	rm -f $(APPL) *.o *.mod
