CXX = g++
CXXFLAGS = -O2 -g
CPPFLAGS =
LDFLAGS =
LDLIBS =

APPS = list_stl.exe set_stl.exe

all: $(APPS)

%.exe: %.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $^

clean:
	rm -f $(APPS) *.o
