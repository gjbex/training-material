#ifndef CONSTRAINED_PARTICLES_HDR
#define CONSTRAINED_PARTICLES_HDR

#include "particles.h"

class Constrained_particles : public Particles {
    private:
        long _leftWall;
        long _right_wall;
        long _collisions;
    public:
        Constrained_particles(const Params& params) :
            Particles(params),
            _leftWall {params.leftWall()},
            _right_wall {params.rightWall()},
            _collisions {0} {}
        ~Constrained_particles() override {};
        void move() override;
        double get_collision_fraction() const override {
            return ((double) _collisions)/get_nr_particles();
        };
};

#endif
