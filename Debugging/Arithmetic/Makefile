CFLAGS = -O2 -g -Wall -Wextra
FFLAGS = -O2 -g -Wall -Wextra
CXXFLAGS = -std=c++14 -O2 -g -Wall -Wextra
LDFLAGS = -lm

all: addition.exe overflow_cpp.exe float_overflow.exe underflow.exe \
        equality.exe float_overflow_nan.exe trace_nan_f90.exe \
        trace_nan_f90_fpe.exe


%_cpp.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

%_f90_fpe.exe: %.f90
	$(FC) $(FFLAGS) -ffpe-trap=invalid,zero,overflow -o $@ $^

%_f90.exe: %.f90
	$(FC) $(FFLAGS) -o $@ $^

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) *.exe *.o *.mod
	$(RM) core core.*
