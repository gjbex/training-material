#ifndef PENDULUM_UTILS_HDR
#define PENDULUM_UTILS_HDR

#include <functional>
#include <tuple>

using Parameters = std::tuple<double, double, double>;

Parameters get_parameters(int argc, char *argv[]);
void integrate(std::function<double(double)> f,
               double delta_t, double max_t);

#endif
