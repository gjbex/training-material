MPIF90 = mpif90
FFLAGS = -O2 -g

APPS = explicit_offsets.exe views.exe create_tasks.exe run_tasks.exe

all: $(APPS)

create_tasks.exe: tasks_mod.o create_tasks.o
	$(MPIF90) $(FFLAGS) -o $@ $^

run_tasks.exe: tasks_mod.o run_tasks.o
	$(MPIF90) $(FFLAGS) -o $@ $^

%.exe: %.f90
	$(MPIF90) $(FFLAGS) -o $@ $^

%.o: %.f90
	$(MPIF90) $(FFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.mod $(APPS) core
