#include <cmath>
#include <iostream>

#include "particle.h"

using namespace std;

inline double sqr(double x) {
    return x*x;
}

void Particle::move(double dx, double dy, double dz) {
    _x += dx;
    _y += dy;
    _z += dz;
}

double Particle::dist(const Particle& other) const {
    return sqrt(sqr(_x - other.x()) + 
                sqr(_y - other.y()) +
                sqr(_z - other.z()));
}

ostream& operator<<(ostream& out, const Particle& p) {
    return out << "(" << p.x() << ", " << p.y() << ", " << p.z() << ")"
           << ", mass = " << p.mass();
}
