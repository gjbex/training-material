MPICC = mpicc
CFLAGS = -O2 -g

APPL = appl1.exe appl2.exe server.exe client.exe 
all: $(APPL)

appl1.exe: appl.c
	$(MPICC) $(CFLAGS) -DAPP_ID="\"application 1\"" -o $@ $^

appl2.exe: appl.c
	$(MPICC) $(CFLAGS) -DAPP_ID="\"application 2\"" -o $@ $^

%.exe: %.o
	$(MPICC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(MPICC) $(CFLAGS) -c $^

clean:
	rm -f $(APPL) *.o
