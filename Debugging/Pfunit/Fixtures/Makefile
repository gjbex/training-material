all: tests.exe

.PRECIOUS: %.F90

ifneq ($(BASEMK_INCLUDED),YES)
include $(PFUNIT)/include/base.mk
endif

FC = gfortran
FFLAGS += -g -I$(PFUNIT)/mod -I.
LIBS = $(PFUNIT)/lib/libpfunit$(LIB_EXT)

tests.exe: tests.o
	$(FC) $(FFLAGS) $(FPPFLAGS) -o $@  \
        $(PFUNIT)/include/driver.F90 $^ $(LIBS)

testSuites.inc: tests.pf

%.F90: %.pf
	$(PFUNIT)/bin/pFUnitParser.py $<  $@

%.o: %.F90
	$(FC) -c $(FFLAGS) $(FPPFLAGS) $<

%.o: %.f90
	$(FC) -c $(FFLAGS) $<

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.mod) $(wildcard *.o)
	$(RM) tests.F90
