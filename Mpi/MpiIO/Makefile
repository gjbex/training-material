MPIF90 = mpif90
FFLAGS = -O2 -g

APPS = explicit_offsets.exe views.exe create_tasks.exe tasks.exe

all: $(APPS)

create_tasks.exe: create_tasks.o tasks_mod.o
	$(MPIF90) $(FFLAGS) -o $@ $^

tasks.exe: tasks.o tasks_mod.o
	$(MPIF90) $(FFLAGS) -o $@ $^

%.exe: %.f90
	$(MPIF90) $(FFLAGS) -o $@ $^

%.o: %.f90
	$(MPIF90) $(FFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.mod $(APPS) core
