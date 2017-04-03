#include <cmath>

#include "pendulum_utils.h"

class Pendulum {
    private:
        double _freq;
        const double pi {acos(-1.0)};
    public:
        Pendulum(const double& freq) : _freq {freq} {};
        double operator()(const double& t) const {
            return cos(2.0*pi*_freq*t);
        };
        double freq() const { return _freq; };
};

int main(int argc, char *argv[]) {
    double freq, delta_t, max_t;
    std::tie(freq, delta_t, max_t) = get_parameters(argc, argv);
    Pendulum pendulum {freq};
    integrate(pendulum, delta_t, max_t);
    return 0;
}
