CXX = g++
CXXFLAGS = -std=c++14 -O2 -g -Wall -Wextra -Wpedantic
OMPFLAGS = -fopenmp
CPPFLAGS = -I/apps/leuven/skylake/2018a/software/tbb/2018_U5-GCCcore-6.4.0/include
LDFLAGS = -L/apps/leuven/skylake/2018a/software/tbb/2018_U5-GCCcore-6.4.0/build/linux_intel64_gcc_cc6.4.0_libc2.17_kernel3.10.0_release/
LDLIBS = -lm

.PRECIOUS: %.o

all: julia_abs.exe julia.exe julia_tbb.exe julia_omp.exe \
     julia_tasks_omp.exe

%_omp.exe: %_omp.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OMPFLAGS) -o $@ $^ $(LDLIBS)

%_tbb.exe: %_tbb.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) -ltbb $(LDLIBS)

%.exe: %.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	$(RM) *.o *.exe
	$(RM) core core.*
