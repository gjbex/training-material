#include "particle.h"

void Particle::move(double t) {
    _x += _v_x*t;
    _y += _v_y*t;
}

double Particle::energy() const {
    return StaticParticle::energy() + mass()*(v_x()*v_x() + v_y()*v_y());
}

std::ostream& operator<<(std::ostream& out, const Particle& p) {
    return out << static_cast<const StaticParticle&>(p) << ", ("
               << p.v_x() << ", " << p.v_y() << ")";
}
