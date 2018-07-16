#ifndef RNG_HDR
#define RNG_HDR

#include <random>

class Rng_builder;

class Rng {
    public:
        double operator()() { return _distr(_engine); };
    private:
        friend class Rng_builder;
        Rng(const double a, const double b, size_t seed, const bool seeded);
        std::mt19937_64 _engine;
        std::uniform_real_distribution<double> _distr;
};

#endif
