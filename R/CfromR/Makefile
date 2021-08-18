all: myRLib.so

myRLib.so: myRLib.c
	R CMD SHLIB $<

clean:
	$(RM) $(wildcard *.o) $(wildcard myRLib.so)
