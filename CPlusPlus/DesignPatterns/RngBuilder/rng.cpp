#include "rng.h"

Rng::Rng(const double a, const double b, size_t seed, const bool seeded) {
    if (!seeded) {
        std::random_device device;
        seed = device();
    }
    _engine = std::mt19937_64(seed);
    _distr = std::uniform_real_distribution<double>(a, b);
}
