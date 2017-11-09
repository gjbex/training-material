CXXFLAGS = -std=c++14 -Wall -Wextra

all: accumulate.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) *.exe *.o
	$(RM) core core.*
