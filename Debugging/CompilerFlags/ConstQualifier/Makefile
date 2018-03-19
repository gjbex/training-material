all: const_qual.exe

warnings:
	$(CC) $(CFLAGS) -Wcast-qual -c const_qual.c

const_qual.exe: const_qual.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) *.o *.exe
	$(RM) core core.*
