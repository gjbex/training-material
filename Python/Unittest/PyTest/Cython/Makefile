VERSION = cpython-34m
PRIMES_LIB = fac_cython.$(VERSION).so

all: $(PRIMES_LIB)

$(PRIMES_LIB): fac_cython.pyx
	python setup.py build_ext --inplace

clean:
	python setup.py clean
	$(RM) fac_cython.c $(PRIMES_LIB)
