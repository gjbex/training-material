#include <ostream>
#include "static_particle.h"

class Particle : public StaticParticle {
    private:
        double _v_x, _v_y;
    public:
        Particle(double x, double y, double v_x, double v_y, double mass)
            : StaticParticle(x, y, mass), _v_x {v_x}, _v_y {v_y} {
            };
        double v_x() const { return _v_x; };
        double v_y() const { return _v_y; };
        void move(double t);
};

std::ostream& operator<<(std::ostream& out, const Particle& p);
