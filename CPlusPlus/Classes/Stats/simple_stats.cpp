#include "stats.h"

std::ostream& operator<<(std::ostream& out, const SimpleStats& stats) {
    return out << "sum = " << stats.sum() << std::endl
               << "n = " << stats.n();
}
