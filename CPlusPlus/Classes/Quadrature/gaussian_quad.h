#ifndef GAUSSIAN_QUAD_HDR
#define GAUSSIAN_QUAD_HDR

#include <vector>
#include "quad.h"

class GaussianQuad : public Quad {
    private:
        std::vector<double> _x;
        std::vector<double> _w;
    public:
        GaussianQuad();
        double integrate(Integrand f, const double a, const double b) const
            override;
};

#endif
