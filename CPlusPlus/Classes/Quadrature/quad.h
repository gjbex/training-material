#ifndef QUAD_HDR
#define QUAD_HDR

#include <functional>

using Integrand = std::function<double(double)>;

class Quad {
    public:
        virtual double integrate(Integrand f,
                                 const double a,
                                 const double b) const  = 0;
};

#endif
