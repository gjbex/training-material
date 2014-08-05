#include <err.h>
#include <math.h>
#include <new>
#include <stdlib.h>

using namespace std;

#include "ising.h"

IsingSystem::IsingSystem(int N, double J, double H, double T) {
    _N = N;
    _J = J;
    _H = H;
    _T = T;
    _s = new (std::nothrow) int[N*N];
    if (_s == NULL)
        errx(1, "can not allocate Ising system");
    for (int i = 0; i < N*N; i++)
        _s[i] = 1.0;
    _M = N*N;
    _E = -J*N*N - H*N;
}

IsingSystem::~IsingSystem() {
    delete[] _s;
}

double IsingSystem::_delta_E(int i, int j) const {
    int left = (i == 0) ? _N - 1 : i;
    int up = (j == 0) ? _N - 1 : j;
    int right = (i == _N - 1) ? 0 : i;
    int down = (j == _N - 1) ? 0 : j;
    return 2.0*_s[i*_N + j]*(_J*(_s[left*_N + j] + _s[i*_N + up] +
                                 _s[right*_N + j] + _s[i*_N + down]) + _H);
}

void IsingSystem::step() {
    for (int i = 0; i < _N; i++)
        for (int j = 0; j < _N; j++) {
            double delta_E = _delta_E(i, j);
            if (delta_E < 0.0 ||
                exp(-delta_E/_T) > ((double) rand())/((double) RAND_MAX)) {
                int idx = i*_N + j;
                _s[idx] = -_s[idx];
                _M += 2.0*_s[idx];
                _E += delta_E;
            }
        }
}

