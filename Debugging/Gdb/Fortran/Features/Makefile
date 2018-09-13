FC = gfortran
FFLAGS = -g -O0 -Wall -Wextra

all: tree.exe display_demo.exe change_command.exe watch_point.exe

tree.exe: tree_mod.o tree.o
	$(FC) $(FFLAGS) -o $@ $^

%.exe: %.o
	$(FC) $(FFLAGS) -o $@ $<

%.o: %.f90
	$(FC) $(FFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.mod) $(wildcard *.o)
	$(RM) core $(wildcard core.*)
