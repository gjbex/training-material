PYX_FILES = julia_cython.pyx julia_cython_omp.pyx
C_FILES = $(patsubst %.pyx,%.c,$(PYX_FILES))
JULIA_LIB = $(patsubst %.c,%.so,$(C_FILES))

all: $(JULIA_LIB)

$(JULIA_LIB): $(PYX_FILES)
	python setup.py build_ext --inplace

clean:
	python setup.py clean
	rm -f $(C_FILES)  $(JULIA_LIB)
