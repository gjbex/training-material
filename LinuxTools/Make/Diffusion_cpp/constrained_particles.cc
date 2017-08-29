#include "constrained_particles.h"

void Constrained_particles::move() {
    _collisions = 0;
    for (size_t i = 0; i < get_nr_particles(); i++)
        if (_positions[i] == _leftWall) {
            _positions[i]++;
            _collisions++;
        } else if (_positions[i] == _right_wall) {
            _positions[i]--;
            _collisions++;
        } else if (_distr(_engine))
            _positions[i]++;
        else
            _positions[i]--;
}
