#ifndef GAUSSIAN_QUAD_HDR
#define GAUSSIAN_QUAD_HDR

#include <functional>
#include <vector>

using Integrand = std::function<double(double)>;

class GaussianQuad {
    private:
        std::vector<double> _x;
        std::vector<double> _w;
    public:
        GaussianQuad();
        double integrate(Integrand f, const double a, const double b) const;
};

#endif
