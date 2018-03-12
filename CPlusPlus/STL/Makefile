CXX = g++
CXXFLAGS = -O2 -g --std=c++11 -Wall
CPPFLAGS =
LDFLAGS =
LDLIBS =

APPS = list_stl.exe map_stl.exe set_stl.exe rpn_calc.exe \
       map_functions.exe priority_queue_stl.exe

all: $(APPS)

%.exe: %.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $^

clean:
	rm -f $(APPS) *.o
