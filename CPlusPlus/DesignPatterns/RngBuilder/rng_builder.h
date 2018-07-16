#ifndef RNG_BUILDER_HDR
#define RNG_BUILDER_HDR

#include "rng.h"

class Rng_builder {
    public:
        Rng_builder() : _a {_a_default}, _b {_b_default},
            _seed {0}, _seeded {false} {};
        Rng_builder& lower(double value) { _a = value; return *this; };
        Rng_builder& upper(double value) { _b = value; return *this; };
        Rng_builder& seed(size_t value) {
            _seed = value;
            _seeded = true;
            return *this;
        };
        Rng build() const { return Rng(_a, _b, _seed, _seeded); };
        Rng_builder& reset();
    private:
        double _a;
        double _b;
        size_t _seed;
        bool _seeded;
        static constexpr double _a_default {0.0};
        static constexpr double _b_default {1.0};
};

#endif
