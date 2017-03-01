#include "particle.h"

void Particle::move(double t) {
    _x += _v_x*t;
    _y += _v_y*t;
}

std::ostream& operator<<(std::ostream& out, const Particle& p) {
    return out << (StaticParticle) p << ", ("
               << p.v_x() << ", " << p.v_y() << ")";
}
