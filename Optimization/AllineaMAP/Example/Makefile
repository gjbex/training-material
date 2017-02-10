F90 = mpif90
FFLAGS = -g -O2 -Wall

APPL = diffusion_01.exe

all: $(APPL)

diffusion_%.exe: cl_params.o system_%.o main_%.o
	$(F90) $(FFLAGS) -o $@ $^

%.o: %.f90
	$(F90) $(FFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.mod $(APPL)
