FC = mpif90
FFLAGS = -g

all: message_size.exe message_type.exe message_int_size.exe \
     buffer_overlap.exe buffer_size.exe

%.exe: %.o
	$(FC) $(FFLAGS) -o $@ $<

%.o: %.f90
	$(FC) $(FFLAGS) -c $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
	$(RM) -r MUST_Output-files MUST_Output.html must_temp
	$(RM) $(wildcard *.stf) $(wildcard *.stf.*) $(wildcard *.prot)
