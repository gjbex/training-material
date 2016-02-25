VERSION = cpython-34m
POINTERS_LIB = pointers.$(VERSION).so

all: $(POINTERS_LIB)

$(POINTERS_LIB): pointers.pyx
	python setup.py build_ext --inplace

clean:
	python setup.py clean
	rm -f pointers.c $(POINTERS_LIB)
