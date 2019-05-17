CXX = g++
CXXFLAGS = -O2 -g -Wall -Wextra -Wpedantic
CPPFLAGS = -I/usr/include/eigen3/
LDLIBS = -lm

all: matrix_product.exe read_matrix.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $< $(LDLIBS)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
