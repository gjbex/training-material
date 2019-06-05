CC = gcc
OPTFLAGS = -O2
CFLAGS = -g -Wall -Wextra
FC = gfortran
FFLAGS = -g -Wall -Wextra
FFPEFLAGS = -ffpe-trap=invalid,zero,overflow,underflow
CFPEFLAGS = -O0 -D_GNU_SOURCE -DFPE_TRAP 
CXXFLAGS = -std=c++14 -g -Wall -Wextra
LDLIBS = -lm

all: addition.exe overflow_cpp.exe float_overflow.exe \
        underflow.exe  underflow_c_fpe.exe underflow_f90_fpe.exe  \
        equality.exe float_overflow_nan.exe trace_nan_f90.exe \
        trace_nan_f90_fpe.exe trace_nan_c.exe trace_nan_c_fpe.exe \
        integer_division_f90.exe associativity.exe nans_infs.exe \
        precision_c.exe



%_cpp.exe: %.cpp
	$(CXX) $(OPTFLAGS) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%_f90_fpe.exe: %.f90
	$(FC) $(FFLAGS) $(FFPEFLAGS) -o $@ $^ $(LDLIBS)

%_f90.exe: %.f90
	$(FC) $(OPTFLAGS) $(FFLAGS) -o $@ $^ $(LDLIBS)

%_c_fpe.exe: %.c
	$(CC) $(CFLAGS) $(CFPEFLAGS) -o $@ $^ $(LDLIBS)

%_c.exe: %.c
	$(CC) $(OPTFLAGS) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.exe: %.o
	$(CC) $(OPTFLAGS) $(CFLAGS) -o $@ $^ $(LDLIBS)

check: check_c check_cpp

check_c: $(wildcard *.c)
	cppcheck --quiet --enable=all --inconclusive \
             --suppress=missingIncludeSystem \
             --language=c --std=c89 --platform=unix64 $^

check_cpp: $(wildcard *.cpp)
	cppcheck --quiet --enable=all --inconclusive \
             --suppress=missingIncludeSystem \
             --language=c++ --std=c++14 --platform=unix64 $^

sanitizer: float_divide_by_zero.exe integer_divide_by_zero.exe

%.exe: %.c
	$(CC) $(CFLAGS) -fsanitize=integer-divide-by-zero \
                    -fsanitize=float-divide-by-zero \
                    -o $@ $< $(LDLIBS)

clean:
	$(RM) *.exe *.o *.mod
	$(RM) core core.*
