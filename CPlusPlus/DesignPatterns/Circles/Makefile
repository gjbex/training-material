CXX = g++
CXXFLAGS = -std=c++17 -O2 -g -Wall -Wextra
CPPFLAGS = -MMD -MP
LDLIBS = -lm

APPL = random_circles.exe circle_overlap.exe
DATA = overlap_data.txt

.PRECIOUS: *.o

all: $(APPL)

data: overlap_data.txt

plot: data plot_overlap_data.plt
	./plot_overlap_data.plt

overlap_data.txt: $(APPL)  generate_overlap_data.sh
	./generate_overlap_data.sh > $@
	
random_circles.exe: circle.o circle_factory.o random_circles.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

circle_overlap.exe: circle.o circle_overlap.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(wildcard *.d)

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o)
	$(RM) $(wildcard *.d)
	$(RM) $(DATA)
	$(RM) core $(wildcard core.*)
