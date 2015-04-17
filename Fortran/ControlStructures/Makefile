F90 = gfortran
FFLAGS = -O2 -g
LDFLAGS =
LIBS = -lm

APPL = forall_test.exe where_test.exe select_test.exe do_test.exe \
       do_while_test.exe block_test.exe

all: $(APPL)

%.exe: %.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c $<

clean:
	rm -f $(APPL) *.o *.mod
