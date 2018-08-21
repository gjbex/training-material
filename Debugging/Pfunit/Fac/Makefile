tests: tests.exe
	- ./$<

ifneq ($(BASEMK_INCLUDED),YES)
include $(PFUNIT)/include/base.mk
endif

FC = gfortran
FFLAGS += -g -I$(PFUNIT)/mod -I.
LIBS = $(PFUNIT)/lib/libpfunit$(LIB_EXT)

SRCS = $(wildcard *.pf)
OBJS = $(SRCS:.pf=.o)
APPL_OBJS = fac_mod.o

tests.exe: $(APPL_OBJS) $(OBJS)
	$(FC) $(FFLAGS) $(FPPFLAGS) -o $@  \
        $(PFUNIT)/include/driver.F90 $(OBJS) $(APPL_OBJS) $(LIBS)

testSuites.inc: $(SRCS)

%.F90: %.pf
	$(PFUNIT)/bin/pFUnitParser.py $<  $@

fac_mod.o: fac_mod.f90
	$(FC) $(FFLAGS) -c $<

%.o: %.F90
	$(FC) -c $(FFLAGS) $(FPPFLAGS) $<

clean:
	$(RM) *.exe
