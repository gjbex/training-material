#ifndef RNG_BUILDER_HDR
#define RNG_BUILDER_HDR

#include "rng.h"

class Rng_builder {
    public:
        Rng_builder() : a_ {a_default_}, b_ {b_default_},
            seed_ {0}, seeded_ {false} {};
        Rng_builder& lower(double value) { a_ = value; return *this; };
        Rng_builder& upper(double value) { b_ = value; return *this; };
        Rng_builder& seed(size_t value) {
            seed_ = value;
            seeded_ = true;
            return *this;
        };
        Rng build() const { return Rng(a_, b_, seed_, seeded_); };
        Rng_builder& reset();
    private:
        double a_;
        double b_;
        size_t seed_;
        bool seeded_;
        static constexpr double a_default_ {0.0};
        static constexpr double b_default_ {1.0};
};

#endif
