#ifndef PARTICLES_HDR
#define PARTICLES_HDR

#include <random>
#include <vector>
#include "params.h"
#include "statistics.h"
#include "distribution.h"

class Particles {
    protected:
        std::vector<int> _positions;
        std::mt19937_64 _engine;
        std::uniform_int_distribution<int> _distr;
    public:
        Particles(const Params& params);
        virtual ~Particles() {};
        auto get_nr_particles() const { return _positions.size(); };
        virtual void move();
        virtual double get_collision_fraction() const { return 0.0; };
        Statistics get_statistics() const;
        Distribution get_distribution() const;
};

#endif
