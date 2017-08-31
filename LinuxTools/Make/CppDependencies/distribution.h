#ifndef DISTRIBUTION_HDR
#define DISTRIBUTION_HDR

#include <iostream>
#include <memory>
#include <vector>
#include "params.h"

class Distribution {
    private:
        long _left;
        long _right;
        long _nr_particles;
        std::vector<long> _distr;
    public:
        Distribution(const long left, const long right) :
            _left {left}, _right {right}, _nr_particles {0} {
            _distr.resize(right - left + 1, 0);
        };
        size_t size() const { return _distr.size(); };
        void add(const long position) {
            _distr[position - left()]++;
            _nr_particles++;
        };
        long left() const { return _left; };
        long right() const { return _right; };
        long nr_particles() const { return _nr_particles; };
        double get(const int i) const {
            return ((double) _distr.at(i - left()))/nr_particles();
        };
        double entropy() const;
        friend std::ostream& operator<<(std::ostream& out,
                                        const Distribution& distr);
};

#endif
