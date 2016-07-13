PYX_FILES = pi_lib.pyx
C_FILES = $(patsubst %.pyx,%.c,$(PYX_FILES))
LIB_FILES = $(patsubst %.c,%.so,$(C_FILES))

all: $(LIB_FILES)

$(LIB_FILES): $(PYX_FILES)
	python setup.py build_ext --inplace

clean:
	python setup.py clean
	rm -f $(C_FILES)  $(LIB_FILES)
