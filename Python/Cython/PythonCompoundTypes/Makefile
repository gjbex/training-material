VERSION = cpython-34m
COMPOUNDS_LIB = compounds.$(VERSION).so

all: $(COMPOUNDS_LIB)

$(COMPOUNDS_LIB): compounds.pyx
	python setup.py build_ext --inplace

clean:
	python setup.py clean
	rm -f compounds.c $(COMPOUNDS_LIB)
