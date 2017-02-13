CXX = g++
CXXFLAGS = -g -O2 -Wall -std=c++14

APPL = hello.exe talk.exe col_dist.exe gcd.exe fac.exe scope.exe

all: $(APPL)

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(APPL) *.o
