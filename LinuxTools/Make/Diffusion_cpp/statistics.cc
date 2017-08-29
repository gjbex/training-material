#include "statistics.h"

void Statistics::check() const {
    if (n() == 0) {
        std::cerr << "### error: no values for statistics" << std::endl;
        std::exit(10);
    }
}

void Statistics::add(const double value) {
    _n++;
    _sum += value;
    _sum2 += value*value;
    if (value < min())
        _min = value;
    if (value > max())
        _max = value;
}

std::ostream& operator<<(std::ostream& out, const Statistics& stats) {
    return out << "n = " << stats.n() << std::endl
               << "sum = " << stats.sum() << std::endl
               << "mean = " << stats.mean() << std::endl
               << "stddev = " << stats.stddev() << std::endl
               << "min = " << stats.min() << std::endl
               << "max = " << stats.max() << std::endl;
}
