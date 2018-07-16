#ifndef SIMPSON_QUAD_HDR
#define SIMPSON_QUAD_HDR

#include <functional>

using Integrand = std::function<double(double)>;

class SimpsonQuad {
    private:
        unsigned _n;
    public:
        SimpsonQuad(unsigned n) : _n {n} {};
        double integrate(Integrand f, const double a, const double b) const;
        unsigned n() const {return _n; };
};

#endif
