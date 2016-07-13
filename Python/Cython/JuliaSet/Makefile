VERSION = cpython-35m
JULIA_LIB = julia_cython.$(VERSION).so julia_cython_omp.$(VERSION).so

all: $(JULIA_LIB)

$(JULIA_LIB): julia_cython.pyx
	python setup.py build_ext --inplace

clean:
	python setup.py clean
	rm -f julia_cython.c $(JULIA_LIB)
