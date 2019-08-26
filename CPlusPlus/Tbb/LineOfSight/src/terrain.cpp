#include <cmath>
#include <iomanip>
#include "terrain.h"

Terrain::Terrain(const size_t n, const double distance,
                 const double delta_mean, const double delta_stddev,
                 const double flat_fraction, const Seed_t seed) {
    const auto n_flat {static_cast<size_t>(ceil(n*flat_fraction))};
    const double dx {distance/(n - 1)};
    for (size_t i = 0; i < n_flat; ++i) {
        distance_.push_back(i*dx);
        altitude_.push_back(0.0);
    }
    std::mt19937 engine;
    engine.seed(seed);
    auto distr {std::normal_distribution<double>(delta_mean, delta_stddev)};
    for (size_t i = n_flat; i < n; ++i) {
        distance_.push_back(i*dx);
        altitude_.push_back(distr(engine) + altitude_[i - 1]);
    }
}

std::ostream& operator<<(std::ostream& out, Terrain& terrain) {
    out << std::setprecision(5) << std::fixed;
    for (size_t i = 0; i < terrain.n(); ++i)
        out << terrain.distance(i) << " " << terrain.altitude(i) << "\n";
    return out;
}

std::istream& operator>>(std::istream& in, Terrain& terrain) {
    double distance {0.0};
    double altitude {0.0};
    while (in >> distance >> altitude) {
        terrain.distance_.push_back(distance);
        terrain.altitude_.push_back(altitude);
    }
    return in;
}
