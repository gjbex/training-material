CXX = g++
CXXFLAGS = -O2 -g -Wall -std=c++14

.PRECIOUS: %.o

all: strings.exe processes.exe reformat_events.exe simple_re_replace.exe \
     case.exe word_counter.exe

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -f *.o *.exe
