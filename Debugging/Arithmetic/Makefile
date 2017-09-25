CFLAGS = -O2 -g -Wall -Wextra
FFLAGS = -O2 -g -Wall -Wextra
CXXFLAGS = -std=c++14 -O2 -g -Wall -Wextra
LDFLAGS = -lm

all: addition.exe overflow_cpp.exe float_overflow.exe \
        underflow.exe  underflow_c_fpe.exe \
        equality.exe float_overflow_nan.exe trace_nan_f90.exe \
        trace_nan_f90_fpe.exe trace_nan_c.exe trace_nan_c_fpe.exe


%_cpp.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%_f90_fpe.exe: %.f90
	$(FC) $(FFLAGS) -ffpe-trap=invalid,zero,overflow -o $@ $^ $(LDFLAGS)

%_f90.exe: %.f90
	$(FC) $(FFLAGS) -o $@ $^ $(LDFLAGS)

%_c_fpe.exe: %.c
	$(CC) -O0 -g -Wall -Wextra -D_GNU_SOURCE -DFPE_TRAP -o $@ $^ $(LDFLAGS)

%_c.exe: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) *.exe *.o *.mod
	$(RM) core core.*
