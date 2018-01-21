OPTFLAGS = -O2
CFLAGS = -g -Wall -Wextra
FFLAGS = -g -Wall -Wextra
FFPEFLAGS = -ffpe-trap=invalid,zero,overflow,underflow
CFPEFLAGS = -O0 -D_GNU_SOURCE -DFPE_TRAP 
CXXFLAGS = -std=c++14 -g -Wall -Wextra
LDFLAGS = -lm

all: addition.exe overflow_cpp.exe float_overflow.exe \
        underflow.exe  underflow_c_fpe.exe underflow_f90_fpe.exe  \
        equality.exe float_overflow_nan.exe trace_nan_f90.exe \
        trace_nan_f90_fpe.exe trace_nan_c.exe trace_nan_c_fpe.exe


%_cpp.exe: %.cpp
	$(CXX) $(OPTFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%_f90_fpe.exe: %.f90
	$(FC) $(FFLAGS) $(FFPEFLAGS) -o $@ $^ $(LDFLAGS)

%_f90.exe: %.f90
	$(FC) $(OPTFLAGS) $(FFLAGS) -o $@ $^ $(LDFLAGS)

%_c_fpe.exe: %.c
	$(CC) $(CFLAGS) $(CFPEFLAGS) -o $@ $^ $(LDFLAGS)

%_c.exe: %.c
	$(CC) $(OPTFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.exe: %.o
	$(CC) $(OPTFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS)

check: $(CHECKS)
	cppcheck --quiet --enable=all --inconclusive \
             --language=c --std=c89 --platform=unix64 $^

clean:
	$(RM) *.exe *.o *.mod
	$(RM) core core.*
