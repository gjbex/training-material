CC = nvcc
CFLAGS = -O3 -std=c++11 -g
LIBS = -lcublas -larmadillo

.PRECIOUS: %.o

APPL = gemm.exe

all: $(APPL)

gemm.exe: gemm.o cl_params.o cl_params_aux.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

gemm.o: gemm.cu
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(APPL) core.*
