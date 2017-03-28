CXX = g++
CXXFLAGS = -g -O2 -Wall -std=c++14

.PRECIOUS: %.o

APPL = hello.exe talk.exe col_dist.exe gcd.exe fac.exe scope.exe swap.exe \
       arrays.exe argument_passing.exe

all: $(APPL)

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(APPL) *.o
