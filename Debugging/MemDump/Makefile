CC = gcc
CFLAGS = -g
CPPFLAGS = -MMD -MP
LDLIBS = -lm

all: arrays_O0.exe

memory_map_O0: map_O0.txt
	./visualize_memdump.py $^

memory_map_O2: map_O2.txt
	./visualize_memdump.py $^

map_O0.txt: arrays_O0.exe
	./$^ 2> $@

map_O2.txt: arrays_O2.exe
	./$^ 2> $@

%_O2.exe: %.o
	$(CC) -O2 -o $@ $< $(LDLIBS)

%_O0.exe: %.o
	$(CC) -O0 -o $@ $< $(LDLIBS)

-include $(wildcard *.d)
clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe) $(wildcard *.d)
	$(RM) $(wildcard core.*) core
	$(RM) map.txt
