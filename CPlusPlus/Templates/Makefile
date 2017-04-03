CXX = g++
CXXFLAGS = -O2 -g -Wall -std=c++14
LIBS = -lm

.PRECIOUS: %.o

APPL = swap.exe sum.exe points.exe pendulum_func_obj.exe pendulum_bind.exe \
       pendulum_lambda.exe

all: $(APPL)

pendulum_func_obj.exe: pendulum_func_obj.o pendulum_utils.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

pendulum_bind.exe: pendulum_bind.o pendulum_utils.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

pendulum_lambda.exe: pendulum_lambda.o pendulum_utils.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(APPL)
