CXX = g++
CXXFLAGS = -std=c++14 -g -O2 -Wall -Wextra

.PRECIOUS: %.o

APPL = hello.exe talk.exe col_dist.exe gcd.exe fac.exe scope.exe swap.exe \
       arrays.exe argument_passing.exe local_namespace_use.exe \
       data_parser.exe

all: $(APPL)

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) $(APPL) *.o
	$(RM) core core.*
