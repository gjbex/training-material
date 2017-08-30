#include <algorithm>
#include "particles.h"

Particles::Particles(const Params& params) {
    _positions.resize(params.nrParticles(), 0);
    _engine.seed(params.seed());
    _distr = std::uniform_int_distribution<int>(0, 1);
}

void Particles::move() {
    for (size_t i = 0; i < get_nr_particles(); i++)
        if (_distr(_engine))
            _positions[i]++;
        else
            _positions[i]--;
}

Statistics Particles::get_statistics() const {
    Statistics stats;
    for (auto position: _positions)
        stats.add(position);
    return stats;
}

Distribution Particles::get_distribution() const {
    auto left_right = std::minmax_element(_positions.cbegin(),
                                          _positions.cend());
    long left = *(left_right.first);
    long right = *(left_right.second);
    Distribution distr(left, right);
    for (auto position: _positions)
        distr.add(position);
    return distr;
}
