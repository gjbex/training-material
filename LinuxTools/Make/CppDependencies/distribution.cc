#include <cmath>
#include "distribution.h"

std::ostream& operator<<(std::ostream& out, const Distribution& distr) {
    for (int i = distr.left(); i <= distr.right(); i++)
        out << i << "," << distr.get(i) << std::endl;
    return out;
}

double Distribution::entropy() const {
    double entropy {0.0};
    for (auto count: _distr)
        if (count > 0) {
            double prob = ((double) count)/nr_particles();
            entropy -= prob*log(prob);
        }
    return entropy;
}
