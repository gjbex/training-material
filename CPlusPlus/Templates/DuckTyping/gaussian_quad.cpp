#include "gaussian_quad.h"

GaussianQuad::GaussianQuad() {
    _w.push_back(0.2955242247147529);
    _w.push_back(0.2955242247147529);
    _w.push_back(0.2692667193099963);
    _w.push_back(0.2692667193099963);
    _w.push_back(0.2190863625159820);
    _w.push_back(0.2190863625159820);
    _w.push_back(0.1494513491505806);
    _w.push_back(0.1494513491505806);
    _w.push_back(0.0666713443086881);
    _w.push_back(0.0666713443086881);

    _x.push_back(-0.1488743389816312);
    _x.push_back(0.1488743389816312);
    _x.push_back(-0.4333953941292472);
    _x.push_back(0.4333953941292472);
    _x.push_back(-0.6794095682990244);
    _x.push_back(0.6794095682990244);
    _x.push_back(-0.8650633666889845);
    _x.push_back(0.8650633666889845);
    _x.push_back(-0.9739065285171717);
    _x.push_back(0.9739065285171717);
}

double GaussianQuad::integrate(Integrand f,
                               const double a, const double b) const {
    double h {0.5*(b - a)};
    double k {0.5*(a + b)};
    double sum {0.0};
    for (unsigned i = 0; i < _w.size(); ++i) {
        sum += _w[i]*f(h*_x[i] + k);
    }
    return h*sum;
}
