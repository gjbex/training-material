F90 = gfortran
FFLAGS = -O2 -g
LDFLAGS =
LIBS = -lm

APPL = forall_test where_test select_test do_test

all: $(APPL)

forall_test: forall_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

where_test: where_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

select_test: select_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

do_test: do_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c $<

clean:
	rm -f $(APPL) *.o *.mod
