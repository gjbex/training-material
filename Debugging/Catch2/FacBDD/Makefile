CXX = g++
CXXFLAGS = -std=c++14 -g -O2 -Wall -Wextra -fPIC
CPPFLAGS = $(shell pkg-config catch --cflags) -MMD -MP

all: fac.exe

checks: test_fac.exe
	LD_LIBRARY_PATH=".:${LD_LIBRARY_PATH}" ./$^

libfac.so: fac.o
	$(CXX) $(CXXFLAGS) -shared -o $@ $< $(LDFLAGS)

fac.exe: fac_main.o libfac.so
	$(CXX) $(CXXFLAGS) -o $@ $^

test_fac.exe: test_fac.o test_main.o libfac.so
	$(CXX) $(CXXFLAGS) -o $@ $^

-include $(wildcard *.d)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe) $(wildcard *.so) \
          $(wildcard *.d)
	$(RM) $(wildcard core.*) core
