CXX = g++
CXXFLAGS = -O2 -g -fPIC
CPPFLAGS = `pkg-config --cflags python3`
LDFLAGS = `pkg-config --libs python3`
LIBS = -lm

OBJS = ising_cxx_wrap.o ising.o

all: _ising_cxx.so

deploy: _ising_cxx.so
	cp _ising_cxx.so ..
	cp ising_cxx.py ..

_ising_cxx.so: $(OBJS)
	$(CXX) -shared $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

ising_cxx_wrap.o: ising_cxx_wrap.cxx
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $<

ising.o: ising.cxx ising.h
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c ising.cxx

ising_cxx_wrap.cxx: ising_cxx.i
	swig -python -c++ $<

show:
	pkg-config --cflags python3
	pkg-config --libs python3

clean:
	rm -f ising_cxx_wrap.cxx *.o _ising_cxx.so ising_cxx.py
