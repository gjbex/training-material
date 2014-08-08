#ifndef ISING_HDR
#define ISING_HDR

#include <stdlib.h>

class IsingSystem {
    private:
        int _N;
        double _J, _H, _T, _M, _E;
        int *_s;
        double _delta_E(int i, int j) const;
    public:
        IsingSystem(int N, double J, double H, double T);
        ~IsingSystem();
        IsingSystem *clone(void);
        int N() const;
        double J() const;
        double H() const;
        double T() const;
        int s(int i, int j) const;
        double magnetization() const;
        double energy() const;
        void step();
        void init_random(int seed);
};

inline int IsingSystem::N() const {
    return _N;
}

inline double IsingSystem::J() const {
    return _J;
}

inline double IsingSystem::H() const {
    return _H;
}

inline double IsingSystem::T() const {
    return _T;
}

inline int IsingSystem::s(int i, int j) const {
    return _s[i*_N + j];
}

inline double IsingSystem::magnetization() const {
    return _M/(_N*_N);
}

inline double IsingSystem::energy() const {
    return _E/(_N*_N);
}

inline void IsingSystem::init_random(int seed) {
    srand(seed);
}

#endif

