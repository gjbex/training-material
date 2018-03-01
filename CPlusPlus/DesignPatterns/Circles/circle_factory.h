#ifndef CIRCLE_FACTORY_HDR
#define CIRCLE_FACTORY_HDR

#include <functional>
#include <random>

#include "circle.h"

class CircleFactory {
    private:
        double _min {0.0};
        double _max {1.0};
        double _radius;
        std::mt19937_64 _engine;
        std::uniform_real_distribution<double> _distr;
        std::function<double()> _random;
    public:
        CircleFactory(const double radius, const int seed);
        Circle create() const;
};

#endif
