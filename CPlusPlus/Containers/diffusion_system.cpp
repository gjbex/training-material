#include <array>
#include <functional>
#include <iostream>
#include <random>

#include "diffusion_system.h"

using namespace std;

ostream& operator<<(ostream& out, const Particle& p) {
    return out << "(" << p.x() << ", " << p.y() << "): "<< p.time();
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
    for (size_t i = 0; i < _grid_size*_grid_size; i++)
        _grid[i] = false;
    _queue = new Particle_queue(cmp);
    for (size_t i = 0; i < _nr_patricles; i++) {
        double time {_time_distr()};
        int x {_pos_distr()};
        int y {_pos_distr()};
        _grid[x*_grid_size + y] = true;
        Particle particle(time, x, y);
        _queue->push(particle);
    }
}

System::~System() {
    delete[] _grid;
    delete _queue;
}

void System::print_queue() const {
    Particle_queue io_queue = *_queue;
    while (!io_queue.empty()) {
        Particle particle = io_queue.top();
        cout << "(" << particle.x() << ", " << particle.y() << "): ";
        cout << particle.time() << endl;
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

Potential_positions System::find_moves(const Particle& particle) {
    Potential_positions pos {{-1}};
    int n {(int) _grid_size};
    int new_x, new_y;
    new_x = particle.x() - 1;
    new_y = particle.y();
    if (new_x >= 0 && !_grid[new_x*n + new_y])
        pos[0] = new_x*n + new_y;
    new_x = particle.x();
    new_y = particle.y() + 1;
    if (new_y < n && !_grid[new_x*n + new_y])
        pos[1] = new_x*n + new_y;
    new_x = particle.x() + 1;
    new_y = particle.y();
    if (new_x < n && !_grid[new_x*n + new_y])
        pos[2] = new_x*n + new_y;
    new_x = particle.x();
    new_y = particle.y() - 1;
    if (new_y >= 0 && !_grid[new_x*n + new_y])
        pos[3] = new_x*n + new_y;
    return pos;
}

double System::update() {
    if (!_queue->empty()) {
        Particle particle {_queue->top()};
        cout << "update" << endl;
        cout << particle << endl;
        _queue->pop();
        double delta_t {particle.time()};
        int new_x {particle.x()};
        int new_y {particle.y()};
        Potential_positions pos {find_moves(particle)};
        int index {_move_distr()};
        if (pos[index] >= 0) {
            int x = pos[index]/_grid_size;
            int y = pos[index] % _grid_size;
            _grid[pos[index]] = false;
            _grid[x*_grid_size + y] = true;
            new_x = x;
            new_y = y;
        }
        particle.update(delta_t + _time_distr(), new_x, new_y);
        _queue->push(particle);
        return delta_t;
    } else {
        cerr << "# error: empty queue" << endl;
        terminate();
    }
}

bool cmp(const Particle& p1, const Particle& p2) {
    return !(p1 < p2);
}
