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
    _move_distr = bind(uniform_int_distribution<int>(0, 3),
                       ref(engine));
    _grid = new bool[_grid_size*_grid_size];
    _queue = new Particle_queue(cmp);
    for (size_t i = 0; i < _grid_size*_grid_size; i++)
        _grid[i] = false;
    for (size_t i = 0; i < _nr_patricles; i++) {
        double time {_time_distr()};
        Coordinates *coords = new Coordinates({_pos_distr(), _pos_distr()});
        _grid[(*coords)[0]*_grid_size + (*coords)[1]] = true;
        Particle particle(time, coords);
        _queue->push(particle);
    }
}

System::~System() {
    delete[] _grid;
    while (!_queue->empty()) {
        Particle particle = _queue->top();
        delete particle.second;
        _queue->pop();
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

Potential_positions System::find_moves(const Coordinates* coords) {
    Potential_positions pos {-1};
    int x = (*coords)[0];
    int y = (*coords)[1];
    int new_x, new_y;
    new_x = x - 1;
    new_y = y;
    if (new_x >= 0 && !(*_grid)[new_x*_grid_size + new_y])
        pos[0] = new_x*n + new_y;
    new_x = x;
    new_y = y + 1;
    if (new_y < _grid_size && !(*_grid)[new_x*_grid_size + new_y])
        pos[1] = new_x*n + new_y;
    new_x = x + 1;
    new_y = y;
    if (new_x < _grid_size && !(*_grid)[new_x*_grid_size + new_y])
        pos[2] = new_x*n + new_y;
    new_x = x;
    new_y = y - 1;
    if (new_y >= 0 && !(*_grid)[new_x*_grid_size + new_y])
        pos[3] = new_x*n + new_y;
    return pos;
}

double System::update() {
    Particle particle = _queue->top();
    double delta_t = particle.first;
    Potential_positions pos = find_moves(particle.second);
    // TODO: select position, move, and requeue
    return delta_t;
}

bool cmp(const Particle& p1, const Particle& p2) {
    return p1.first > p2.first;
}
