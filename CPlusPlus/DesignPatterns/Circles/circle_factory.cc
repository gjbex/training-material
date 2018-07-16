#include <stdexcept>

#include "circle_factory.h"

CircleFactory::CircleFactory(const double radius, const int seed) {
    _radius = radius;
    double lower {_min + radius};
    double upper {_max - radius};
    if (lower >= upper)
        throw std::invalid_argument("radius too large");
    _engine.seed(seed);
    _distr = std::uniform_real_distribution<double>(lower, upper);
    _random = [this] () { return (this->_distr)(this->_engine); };
};

Circle CircleFactory::create() const {
    double x {_random()};
    double y {_random()};
    Circle circle(x, y, _radius);
    return circle;
}
