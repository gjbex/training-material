#ifndef SIMPSON_QUAD_HDR
#define SIMPSON_QUAD_HDR

#include "quad.h"

class SimpsonQuad : public Quad {
    private:
        unsigned _n;
    public:
        SimpsonQuad(unsigned n) : Quad(), _n {n} {};
        double integrate(Integrand f, const double a, const double b) const
            override;
        unsigned n() const {return _n; };
};

#endif
