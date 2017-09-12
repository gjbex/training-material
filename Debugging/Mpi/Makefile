FC = mpif90
FFLAGS = -g

all: diffusion.exe 010_deadlock.exe 012_leak.exe 020_no_allocate.exe \
     030_index_out_of_bounds.exe prototype.exe message_size.exe \
     message_type.exe message_int_size.exe buffer_overlap.exe

%.exe: %.o
	$(FC) $(FFLAGS) -o $@ $<

%.o: %.f90
	$(FC) $(FFLAGS) -c $<

clean:
	$(RM) *.o *.exe
	$(RM)  core core.*
	$(RM) -r MUST_Output-files MUST_Output.html
