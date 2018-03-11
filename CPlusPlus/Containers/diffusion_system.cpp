#include "diffusion_system.h"

using namespace std;

ostream& operator<<(ostream& out, const Particle& p) {
    return out << p._id << ": (" << p.x() << ", " << p.y() << "): "
               << p.mass() << " at " << p.time();
}

System::System(size_t nr_particles, size_t grid_size) {
    _nr_patricles = nr_particles;
    _grid_size = grid_size;
    _engine = new mt19937_64(1234);
    _pos_distr = uniform_int_distribution<int>(0, _grid_size - 1);
    _mass_distr = poisson_distribution<int>(3);
    _move_distr = uniform_int_distribution<int>(0, 3);
    _grid = new bool[_grid_size*_grid_size];
    for (size_t i = 0; i < _grid_size*_grid_size; i++)
        _grid[i] = false;
    _queue = new Particle_queue(cmp);
    for (size_t i = 0; i < _nr_patricles; i++) {
        double mass {1.0 +  _mass_distr(*_engine)};
        int x {_pos_distr(*_engine)};
        int y {_pos_distr(*_engine)};
        _grid[x*_grid_size + y] = true;
        Particle particle(i, mass, x, y, _engine);
        _queue->push(particle);
    }
}

System::~System() {
    delete[] _grid;
    delete _queue;
    delete _engine;
}

void System::print_queue() const {
    Particle_queue io_queue = *_queue;
    while (!io_queue.empty()) {
        Particle particle = io_queue.top();
        cout << particle << endl;
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

int* System::find_moves(const Particle& particle) {
    int* pos = new int[4];
    for (int i = 0; i < 4; i++)
        pos[i] = -1;
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
        _queue->pop();
        double delta_t {particle.time()};
        int new_x {particle.x()};
        int new_y {particle.y()};
        int* pos {find_moves(particle)};
        int index = _move_distr(*_engine);
        if (pos[index] >= 0) {
            int x = pos[index]/_grid_size;
            int y = pos[index] % _grid_size;
            _grid[pos[index]] = true;
            _grid[particle.x()*_grid_size + particle.y()] = false;
            new_x = x;
            new_y = y;
        }
        delete[] pos;
        particle.update(new_x, new_y);
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
