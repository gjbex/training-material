#include <cmath>
#include <functional>
#include <iostream>
#include <random>

#include "particles.h"

using namespace std;

auto mass_distr = bind(uniform_real_distribution<double>(0.0, 1.0),
                       mt19937_64(1234));
double sqr(double x) {
    return x*x;
}

Particle init_particle(std::function<double()> pos_distr,
                       std::function<double()> mass_distr,
                       std::function<int()> charge_distr) {
    Particle p;
    p.x = pos_distr();
    p.y = pos_distr();
    p.z = pos_distr();
    p.mass = mass_distr();
    p.charge = charge_distr() == 0 ? -1 : 1;
    return p;
}

double dist(const Particle& p1, const Particle& p2) {
    return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y) + sqr(p1.z - p2.z));
}

double e_force(const Particle& p1, const Particle& p2) {
    const double q_e {1.6021e-19};
    const double k_c {8.98755e9};
    double r {dist(p1, p2)};
    return -k_c*p1.charge*p2.charge*sqr(q_e/r);
}


ostream& operator<<(ostream& out, const Particle& p) {
    return out << "(" << p.x << ", " << p.y << ", " << p.z << ")"
               << ", mass = " << p.mass << ", charge = " << p.charge;
}
