all: fail_icc.exe succeed_gcc.exe

warnings:
	icc -O2 -g -Wall -c spooky_macro.c
	icc -O2 -g -Wall -Wremarks -Wchecks -w3 -c spooky_macro.c
	gcc -O2 -g -c spooky_macro.c
	gcc -O2 -g -Wall -c spooky_macro.c
	gcc -O2 -g -Wfloat-equal -c spooky_macro.c
	rm *.o

fail_icc.exe: spooky_macro.c
	icc -O2 -g -o $@ $<

succeed_gcc.exe: spooky_macro.c
	gcc -O2 -g -o $@ $<

clean:
	rm -f *.o *.exe
