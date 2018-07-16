CXX = g++
CXXFLAGS = -O2 -g --std=c++11 -Wall
CPPFLAGS =
LDFLAGS =
LDLIBS =

APPS = list_stl_orig.exe priority_queue_stl_orig.exe \
       list_stl_fixed.exe priority_queue_stl_fixed.exe

ORIG = list_stl_orig.cpp priority_queue_stl_orig.cpp
FIXED = list_stl_fixed.cpp priority_queue_stl_fixed.cpp

check: $(ORIG) $(FIXED)
	@echo "originals:"
	cppcheck --quiet --enable=all --language=c++ --std=c++14 $(ORIG)
	@echo "fixed:"
	cppcheck --quiet --enable=all --language=c++ --std=c++14 $(FIXED)
    
all: $(APPS)

%.exe: %.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $^

clean:
	rm -f $(APPS) *.o
