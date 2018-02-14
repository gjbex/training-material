CXX = g++
CXXFLAGS = -std=c++17 -O2 -g -Wall -Wextra

all: if_init.exe while_init.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) *.o *.exe
	$(RM) core core.*
