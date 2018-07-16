#include <iomanip>
#include <iostream>
#include <memory>

#include "simpson_quad.h"
#include "gaussian_quad.h"

double func(double x) {
    return 3.0*x*x - 2.0*x + 5.0;
}

template<typename T>
void compute_quads(T quad, Integrand f) {
    for (double x = 1.0; x <= 5.0; x += 1.0)
        std::cout << std::fixed << std::setprecision(15)
                  << quad.integrate(f, -x, x) << std::endl;
}

int main(int argc, char *argv[]) {
    std::string method("simpson");
    if (argc > 1)
        method = std::string(argv[1]);
    if (method == "simpson") {
        SimpsonQuad quad(10);
        compute_quads(quad, func);
    } else if (method == "gaussian") {
        GaussianQuad quad;
        compute_quads(quad, func);
    } else {
        std::cerr << "### error: unknown quadrature method" << std::endl;
        return 1;
    }
    return 0;
};
