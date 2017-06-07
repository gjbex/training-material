CC = nvcc
CFLAGS = -O3 -std=c++11 -g
LIBS = -lcublas -larmadillo

APPL = gemm.exe

all: $(APPL)

%.exe: %.cu
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

clean:
	rm -f *.o $(APPL) core.*
