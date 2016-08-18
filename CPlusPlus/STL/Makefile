CXX = g++
CXXFLAGS = -O2 -g --std=c++11
CPPFLAGS =
LDFLAGS =
LDLIBS =

APPS = list_stl.exe map_stl.exe set_stl.exe

all: $(APPS)

%.exe: %.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $^

clean:
	rm -f $(APPS) *.o
