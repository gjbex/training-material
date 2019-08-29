#ifndef EQUATIONS_HDR
#define EQUATIONS_HDR

#include <iostream>
#include <random>
#include <string>
#include <vector>

using Seed_t = std::mt19937_64::result_type;

class Equations {
    private:
        std::vector<double> coeff_;
        std::vector<double> rhs_;
        int nr_eqns_;
    public:
        Equations(const size_t nr_eqns, const Seed_t seed);
        Equations(std::istream& in);
        size_t nr_eqns() const { return nr_eqns_; }
        double coeff(const size_t eq_nr, const size_t coeff_nr) const {
            if (coeff_nr > eq_nr)
                throw std::out_of_range("coeff. nr. (" + std::to_string(coeff_nr) +
                                        ") > eq. nr. (" + std::to_string(eq_nr) + ")");
            size_t index {eq_nr*(eq_nr + 1)/2 + coeff_nr};
            if (index >= coeff_.size())
                throw std::out_of_range("coeff. index (" + std::to_string(index) +
                                        ") out of bounds");
            return coeff_[index];
        }
        double rhs(const size_t eq_nr) const {
            if (eq_nr >= rhs_.size())
                throw std::out_of_range("r.h.s. index (" + std::to_string(eq_nr) +
                                        ") out of bounds");
            return rhs_[eq_nr];
        }
        friend std::ostream& operator<<(std::ostream& out, Equations& eqns);
};

#endif
