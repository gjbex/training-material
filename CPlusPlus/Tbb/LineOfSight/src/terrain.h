#ifndef TERRAIN_HDR
#define TERRAIN_HDR

#include <cmath>
#include <iostream>
#include <random>
#include <vector>

using Seed_t = std::mt19937::result_type;

class Terrain {
    private:
        std::vector<double> distance_;
        std::vector<double> altitude_;
    public:
        Terrain(const size_t n, const double distance,
                const double delta_mean, const double alt_stddev,
                const double flat_fraction, const Seed_t seed);
        Terrain(std::istream& in) { in >> *this; }
        double distance(const size_t i) const { return distance_[i]; }
        double altitude(const size_t i) const { return altitude_[i]; }
        size_t n() const { return distance_.size(); }
        friend std::ostream& operator<<(std::ostream& out, Terrain& terrain);
        friend std::istream& operator>>(std::istream& in, Terrain& terrain);
};

#endif
