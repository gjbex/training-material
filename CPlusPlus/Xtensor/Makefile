CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
CPPFLAGS = -I/usr/local/software/xtl/0.5.1/include \
		   -I/usr/local/software/xtensor/0.19.1/include \
		   -I/usr/local/software/xtensor-blas/0.15.0/include
LDLIBS = -lm

all: elementwise.exe svd.exe

svd.exe: svd.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $< $(LDLIBS) -lblas -llapack

%.exe: %.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $< $(LDLIBS)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
