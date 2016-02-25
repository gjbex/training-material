VERSION = cpython-34m
HELLO_WORLD_LIB = hello_world.$(VERSION).so

all: $(HELLO_WORLD_LIB)

$(HELLO_WORLD_LIB): hello_world.pyx
	python setup.py build_ext --inplace

clean:
	python setup.py clean
	rm -f hello_world.c $(HELLO_WORLD_LIB)
