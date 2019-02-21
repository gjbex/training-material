#include <cmath>
#include <iostream>

#include "particle.h"

namespace particle {

    inline double sqr(double x) {
        return x*x;
    }

    void Particle::move(double dx, double dy, double dz) {
        x_ += dx;
        y_ += dy;
        z_ += dz;
    }

    double Particle::dist(const Particle& other) const {
        return sqrt(sqr(x_ - other.x()) + 
                    sqr(y_ - other.y()) +
                    sqr(z_ - other.z()));
    }

    std::ostream& operator<<(std::ostream& out, const Particle& p) {
        return out << "(" << p.x() << ", " << p.y() << ", " << p.z() << ")"
               << ", mass = " << p.mass();
    }

};
