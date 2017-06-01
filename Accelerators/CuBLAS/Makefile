CC = nvcc
CFLAGS = -O3 -std=c++11 -g
LDFLAGS = -lcublas

APPL = gemm.exe

all: $(APPL)

%.exe: %.cu
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f *.o $(APPL) core.*
