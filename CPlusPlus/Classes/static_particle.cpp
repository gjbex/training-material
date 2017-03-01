#include <cmath>
#include <iostream>

#include "static_particle.h"

using namespace std;

inline double sqr(double x) {
    return x*x;
}

double StaticParticle::dist(const StaticParticle& other) const {
    return sqrt(sqr(_x - other.x()) + sqr(_y - other.y()));
}

ostream& operator<<(ostream& out, const StaticParticle& p) {
    return out << "(" << p.x() << ", " << p.y() << ")"
           << ", mass = " << p.mass();
}
