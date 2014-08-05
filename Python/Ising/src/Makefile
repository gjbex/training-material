CXX = g++
CXXFLAGS = -O2 -g
CPPFLAGS = -I/usr/include/python2.7
LDFLAGS =
LIBS = -lm

OBJS = ising_cxx_wrap.o ising.o

all: _ising_cxx.so

deploy: _ising_cxx.so
	cp _ising_cxx.so ..
	cp ising_cxx.py ..

_ising_cxx.so: $(OBJS)
	$(CXX) -shared $(CXXFLAGS) $(CPPFLAGS) -o $@ $(OBJS)

ising_cxx_wrap.o: ising_cxx_wrap.cxx
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $<

ising.o: ising.cxx ising.h
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c ising.cxx

ising_cxx_wrap.cxx: ising_cxx.i
	swig -python -c++ $<

clean:
	rm -f ising_cxx_wrap.cxx *.o _ising_cxx.so ising_cxx.py
