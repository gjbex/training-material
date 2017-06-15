#include <cmath>
#include <functional>

#include "pendulum_utils.h"

const double pi {acos(-1.0)};

double pendulum_func(double t, double freq) {
    return cos(2.0*pi*freq*t);
}

int main(int argc, char *argv[]) {
    double freq, delta_t, max_t;
    std::tie(freq, delta_t, max_t) = get_parameters(argc, argv);
    {
        using namespace std::placeholders;
        auto pendulum = std::bind(pendulum_func, _1, freq);
        integrate(pendulum, delta_t, max_t);
    }
    return 0;
}
