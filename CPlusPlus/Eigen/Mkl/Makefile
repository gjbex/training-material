CXX = icpc
CXXFLAGS = -std=c++14 -g -O2 -Wall -Wextra
CPPFLAGS =  -I${MKLROOT}/include
LDFLAGS =  -L${MKLROOT}/lib/intel64
LDLIBS = -lmkl_intel_lp64 -lmkl_tbb_thread -lmkl_core -ltbb -lstdc++ -lpthread -lm -ldl

all: matrix_product.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
