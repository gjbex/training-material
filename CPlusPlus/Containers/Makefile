CXX = g++
CXXFLAGS = -O2 -g -Wall -std=c++14
LIBS = -lm

APPL = tuple.exe vector.exe list.exe set.exe \
       stats.exe dim_nrs.exe dim_nr_counts.exe split_string.exe

all: $(APPL)

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(APPL) *.o
