VERSION = cpython-34m
AVERAGE_LIB = average.$(VERSION).so

all: $(AVERAGE_LIB)

$(AVERAGE_LIB): average.pyx
	python setup.py build_ext --inplace

clean:
	python setup.py clean
	rm -f average.c $(AVERAGE_LIB)
