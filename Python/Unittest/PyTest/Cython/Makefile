VERSION = cpython-34m
PRIMES_LIB = fac_cython.$(VERSION).so

all: $(PRIMES_LIB)

test: $(PRIMES_LIB) test_fac.py
	pytest

$(PRIMES_LIB): fac_cython.pyx
	python setup.py build_ext --inplace

clean:
	python setup.py clean
	$(RM) fac_cython.c $(PRIMES_LIB)
