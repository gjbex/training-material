#include <iomanip>
#include <iostream>
#include <memory>

#include "quad.h"
#include "simpson_quad.h"
#include "gaussian_quad.h"

double func(double x) {
    return 3.0*x*x - 2.0*x + 5.0;
}

using QuadPtr = std::unique_ptr<Quad>;

void compute_quads(QuadPtr quad, Integrand f) {
    for (double x = 1.0; x <= 5.0; x += 1.0)
        std::cout << std::fixed << std::setprecision(15)
                  << quad->integrate(f, -x, x) << std::endl;
}

int main(int argc, char *argv[]) {
    std::string method("simpson");
    if (argc > 1)
        method = std::string(argv[1]);
    QuadPtr quad;
    if (method == "simpson") {
        quad = std::make_unique<SimpsonQuad>(10);
    } else if (method == "gaussian") {
        quad = std::make_unique<GaussianQuad>();
    } else {
        std::cerr << "### error: unknown quadrature method" << std::endl;
        return 1;
    }
    compute_quads(std::move(quad), func);
    return 0;
};
