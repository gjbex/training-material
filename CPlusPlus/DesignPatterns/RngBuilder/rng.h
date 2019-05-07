#ifndef RNG_HDR
#define RNG_HDR

#include <random>

class Rng_builder;

class Rng {
    public:
        double operator()() { return distr_(engine_); };
    private:
        friend class Rng_builder;
        Rng(const double a, const double b, size_t seed, const bool seeded);
        std::mt19937_64 engine_;
        std::uniform_real_distribution<double> distr_;
};

#endif
