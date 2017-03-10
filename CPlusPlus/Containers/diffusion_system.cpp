#include <array>
#include <functional>
#include <iostream>
#include <random>

#include "diffusion_system.h"

using namespace std;

typedef array<size_t, 4> Potential_positions;

Potential_positions compute_moves(const Coordinates* coords,
                                  const bool* grid, size_t grid_size) {
    Potential_positions moves;
    return moves;
}

System::System(size_t nr_particles, size_t grid_size) {
    _nr_patricles = nr_particles;
    _grid_size = grid_size;
    auto engine {mt19937_64(1234)};
    _pos_distr = bind(uniform_int_distribution<int>(0, _grid_size - 1),
                      ref(engine));
    _time_distr = bind(gamma_distribution<double>(3.0, 1.0),
                       ref(engine));
    _grid = new bool[_grid_size*_grid_size];
    _queue = new Particle_queue(cmp);
    for (size_t i = 0; i < _grid_size*_grid_size; i++)
        _grid[i] = false;
    for (size_t i = 0; i < _nr_patricles; i++) {
        double time {_time_distr()};
        Coordinates *coords = new Coordinates({_pos_distr(), _pos_distr()});
        cout << "(" << (*coords)[0] << ", " << (*coords)[1] << ")\n";
        _grid[(*coords)[0]*_grid_size + (*coords)[1]] = true;
        Particle particle(time, coords);
        _queue->push(particle);
    }
}

System::~System() {
    delete[] _grid;
    while (!_queue.empty()) {
        Particle particle = _queue.top();
        delete particle.second;
        _queue.pop();
    }
    delete _queue;
}

void System::print_queue() const {
    Particle_queue io_queue = *_queue;
    while (!io_queue.empty()) {
        Particle particle = io_queue.top();
        Coordinates *coords = particle.second;
        cout << "(" << (*coords)[0] << ", " << (*coords)[1] << "): ";
        cout << particle.first << endl;
        io_queue.pop();
    }
}

void System::print_grid() const {
    cout << "+";
    for (size_t i = 0; i < _grid_size; i++)
        cout << "-";
    cout << "+" << endl;
    for (size_t i = 0; i < _grid_size; i++) {
        cout << "|";
        for (size_t j = 0; j < _grid_size; j++)
            cout << (_grid[i*_grid_size + j] ? 'x' : ' ');
        cout << "|" << endl;
    }
    cout << "+";
    for (size_t i = 0; i < _grid_size; i++)
        cout << "-";
    cout << "+" << endl;
}

bool cmp(const Particle& p1, const Particle& p2) {
    return p1.first > p2.first;
}
