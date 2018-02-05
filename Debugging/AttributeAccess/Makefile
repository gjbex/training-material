FC = gfortran
FFLAGS = -O2 -g -Wall -Wextra
LIBS = -lm

all: stats.exe stats_private.exe

%.exe: %_mod.o %.o
	$(FC) $(FFLAGS) -o $@ $^ $(LIBS)

stats_private.o: stats_private.f90
	@echo "\n!!! Compilatin intentionally fails\n"
	$(FC) $(FFLAGS) -c -o $@ $<

%.o: %.f90
	$(FC) $(FFLAGS) -c -o $@ $<

clean:
	$(RM) *.exe *.o *.mod
	$(RM) core core.*
