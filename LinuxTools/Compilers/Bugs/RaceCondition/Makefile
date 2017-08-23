ICC = icc
ICFLAGS += -O2 -g -Wall -Wremarks -Wchecks -w3 -fp-model precise

GCC = gcc
GCFLAGS += -O2 -g -Wall

APPL = icc_fail.exe icc_succeed.exe

all: fail_icc.exe succeed_icc.exe fail_gcc.exe succeed_gcc.exe

fail_icc.exe: spooky_macro.c
	$(ICC) $(ICFLAGS) -DFAIL -o $@ $<

fail_gcc.exe: spooky_macro.c
	$(GCC) $(GCFLAGS) -DFAIL -o $@ $<

succeed_icc.exe: spooky_macro.c
	$(ICC) $(ICFLAGS) -o $@ $<

succeed_gcc.exe: spooky_macro.c
	$(GCC) $(GCFLAGS) -o $@ $<

clean:
	rm -f *.o *.exe
