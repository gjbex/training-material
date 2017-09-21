CFLAGS = -O2 -g -Wall -Wextra
CXXFLAGS = -std=c++14 -O2 -g -Wall -Wextra
LDFLAGS = -lm

all: addition.exe overflow.exe float_overflow.exe underflow.exe \
        equality.exe

overflow.exe: overflow.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) *.exe *.o
	$(RM) core core.*
