CXX = g++
CXXFLAGS = -std=c++14 -O2 -g -Wall -Wextra
CPPFLAGS = -MMD -MP
LIBS = -lm

APPS = struct_particles.exe class_particles.exe charged_particles.exe \
       stats_compute.exe
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)
DEPS = $(SRCS:%.cpp=%.d)

all: $(APPS)

stats_compute.exe: stats_compute.o stats.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	$(RM) $(APPS) $(OBJS)
	$(RM) $(DEPS)
	$(RM) core $(wildcard core.*)
