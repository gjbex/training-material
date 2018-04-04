all: implicit_not_none.exe implicit_none.exe

warnings:
	-$(FC) $(FFLAGS) -fimplicit-none -c implicit_not_none.f90
	-$(FC) $(FFLAGS) -fimplicit-none -c implicit_none.f90

%.exe: %.f90
	$(FC) $(FFLAGS) -o $@ $<

clean:
	$(RM) *.o *.mod *.exe
	$(RM) core core.*
