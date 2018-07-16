all: shadow_okay.exe shadow_bug.exe

warnings:
	$(CC) $(CFLAGS) -DHAS_BUG -Wshadow -c shadow.c

shadow_okay.exe: shadow.c
	$(CC) $(CFLAGS) -o $@ $<

shadow_bug.exe: shadow.c
	$(CC) $(CFLAGS) -DHAS_BUG -o $@ $<

clean:
	$(RM) *.o *.exe
	$(RM) core core.*
