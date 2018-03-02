VERSION = cpython-36m-x86_64-linux-gnu
FAC_LIB = fac_cython.$(VERSION).so

all: $(FAC_LIB)

test: $(FAC_LIB) test_fac.py
	pytest

$(FAC_LIB): fac_cython.pyx
	python setup.py build_ext --inplace

clean:
	python setup.py clean
	$(RM) fac_cython.c $(FAC_LIB)
