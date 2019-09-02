#include <cmath>
#include "equations.h"

std::vector<double> solve_serial(const Equations& eqns) {
    if (eqns.nr_eqns() == 0)
        throw std::invalid_argument("no equations in set");
    std::vector<double> x;
    x.push_back(eqns.rhs(0)/eqns.coeff(0, 0));
    for (size_t eq_nr = 1; eq_nr < eqns.nr_eqns(); ++eq_nr) {
        double sum {0.0};
        for (size_t coeff_nr = 0; coeff_nr < eq_nr; ++coeff_nr)
            sum += eqns.coeff(eq_nr, coeff_nr)*x[coeff_nr];
        x.push_back((eqns.rhs(eq_nr) - sum)/eqns.coeff(eq_nr, eq_nr));
    }
    return x;
}

std::vector<double> check_serial(const Equations& eqns, const std::vector<double> x) {
    std::vector<double> delta;
    for (size_t eq_nr = 0; eq_nr < eqns.nr_eqns(); ++eq_nr) {
        double sum {0.0};
        for (size_t coeff_nr = 0; coeff_nr <= eq_nr; ++coeff_nr)
            sum += eqns.coeff(eq_nr, coeff_nr)*x[coeff_nr];
        delta.push_back(abs((sum - eqns.rhs(eq_nr))/x[eq_nr]));
    }
    return delta;
}
