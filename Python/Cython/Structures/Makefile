VERSION = cpython-34m
POINT_LIB = point.$(VERSION).so

all: $(POINT_LIB)

$(POINT_LIB): point.pyx
	python setup.py build_ext --inplace

clean:
	python setup.py clean
	rm -f point.c $(POINT_LIB)
