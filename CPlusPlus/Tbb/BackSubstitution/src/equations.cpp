#include "equations.h"

Equations::Equations(const size_t nr_eqns, const Seed_t seed) {
    if (nr_eqns == 0)
        throw std::invalid_argument("creating empty set of equations");
    std::mt19937_64 engine;
    engine.seed(seed);
    std::normal_distribution<double> distr(10.0, 1.0);
    nr_eqns_ = nr_eqns;
    for (size_t coeff_nr = 0; coeff_nr < nr_eqns*(nr_eqns + 1)/2; ++coeff_nr)
        coeff_.push_back(distr(engine));
    for (size_t eq_nr = 0; eq_nr < nr_eqns; ++eq_nr)
        rhs_.push_back(distr(engine));
}

Equations::Equations(std::istream& in) {
    nr_eqns_ = 0;
    int nr_to_read {2};
    int nr_read {0};
    double value {0.0};
    while (in >> value) {
        if (++nr_read == nr_to_read) {
            ++nr_eqns_;
            ++nr_to_read;
            nr_read = 0;
            rhs_.push_back(value);
        } else {
            coeff_.push_back(value);
        }
    }
}

std::ostream& operator<<(std::ostream& out, Equations& eqns) {
    for (size_t eq_nr = 0; eq_nr < eqns.nr_eqns(); ++eq_nr) {
        for (size_t coeff_nr = 0; coeff_nr <= eq_nr; ++coeff_nr)
            out << eqns.coeff(eq_nr, coeff_nr) << " ";
        out << eqns.rhs(eq_nr) << "\n";
    }
    return out;
}
