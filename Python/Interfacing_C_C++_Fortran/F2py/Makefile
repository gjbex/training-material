all: comp_pi.so array_utils.so

array_utils.so: array_utils.f90
	f2py3 -c -m array_utils $<

comp_pi.so: pi.f90
	f2py3 -c -m comp_pi $<

clean:
	$(RM) $(wildcard *.so) $(wildcard *.pyc) \
	$(RM) core $(wildcard core.*)
