CC = mpicc
CFLAGS = -Wall -Wextra -g

all: multi_group.exe

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) #(wildcard *.o) $(wildcard *.exe)
