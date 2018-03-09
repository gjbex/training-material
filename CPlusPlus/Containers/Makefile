CXX = g++
CXXFLAGS = -O2 -g -Wall -std=c++14
LIBS = -lm

.PRECIOUS: %.o

APPL = cosine_similarity.exe synthesizer.exe \
       tuple.exe vector.exe list.exe set.exe \
       stats.exe dim_nrs.exe dim_nr_counts.exe split_string.exe \
       point_distances.exe diffusion.exe aggregate_data.exe

all: $(APPL)

diffusion.exe: diffusion_system.o diffusion_main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(APPL) *.o
