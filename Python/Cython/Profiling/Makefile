VERSION = cpython-35m-x86_64-linux-gnu

QUAD_LIBS = quad.$(VERSION).so quad_prof.$(VERSION).so \
            quad_prof_indiv.$(VERSION).so

all: $(QUAD_LIBS)

%.$(VERSION).so: %.pyx
	python setup.py build_ext --inplace

clean:
	python setup.py clean
	rm -f *.c $(QUAD_LIBS)
