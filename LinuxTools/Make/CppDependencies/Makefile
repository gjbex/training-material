CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -O2 -g
CPPFLAGS = -MMD -MP
LDfLaGS = -lm

SRCS = $(wildcard *.cc)
OBJS = params.o statistics.o particles.o constrained_particles.o \
       distribution.o

APPS = walk.exe distr.exe entropy.exe
all: $(APPS)

%.exe: %.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDfLaGS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(SRCS:%.cc=%.d)

clean:
	$(RM) $(APPS) *.o *.d
	$(RM) core core.*

.PRECIOUS: %.o
