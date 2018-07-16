CXX = g++
CXXFLAGS = -std=c++14 -O2 -g -Wall -Wextra
LDLIBS = -lm

.PRECIOUS: %.o

all: cosine_similarity.exe synthesizer.exe \
        tuple.exe vector.exe list.exe set.exe \
        stats.exe dim_nrs.exe dim_nr_counts.exe split_string.exe \
        point_distances.exe diffusion.exe aggregate_data.exe \
        rpn_calc.exe

diffusion.exe: diffusion_system.o diffusion_main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) $(wildcard core.*) core
