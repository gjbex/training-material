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
    integrate([=](double t) { return pendulum_func(t, freq); },
              delta_t, max_t);
    return 0;
}
