#include <cmath>

#include "stats.h"

double Stats::stddev() const {
    using std::sqrt;
    return sqrt((sum2() - sum()*sum()/n())/(n() - 1));
}

std::ostream& operator<<(std::ostream& out, const Stats& stats) {
    return out << (SimpleStats) stats << std::endl
               << "sum2 = " << stats.sum2();
}
