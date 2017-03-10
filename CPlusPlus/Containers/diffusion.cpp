#include <array>
#include <functional>
#include <iostream>
#include <queue>
#include <random>
#include <vector>

using namespace std;

typedef array<int, 2> Coordinates;
typedef pair<double, Coordinates*> Particle;

bool cmp(const Particle& p1, const Particle& p2) {
    return p1.first > p2.first;
}
typedef function<bool(const Particle&, const Particle&)> cmp_t;

typedef priority_queue<Particle, vector<Particle>, cmp_t>
    Particle_queue;
typedef pair<Particle_queue, bool*> System;

typedef array<size_t, 4> Potential_positions;

Potential_positions compute_moves(const Coordinates* coords,
                                  const bool* grid, size_t grid_size) {
    Potential_positions moves;
    return moves;
}

System init_system(size_t n, function<int()> pos_distr,
                             function<double()> time_distr) {
    Particle_queue queue(cmp);
    bool *grid = new bool[n*n];
    for (size_t i = 0; i < n*n; i++)
        grid[i] = false;
    for (size_t i = 0; i < n; i++) {
        double time {time_distr()};
        Coordinates *coords = new Coordinates({pos_distr(), pos_distr()});
        grid[(*coords)[0]*n + (*coords)[1]] = true;
        Particle particle(time, coords);
        queue.push(particle);
    }
    return System(queue, grid);
}

void print_queue(const Particle_queue& queue) {
    Particle_queue io_queue = queue;
    while (!io_queue.empty()) {
        Particle particle = io_queue.top();
        Coordinates *coords = particle.second;
        cout << "(" << (*coords)[0] << ", " << (*coords)[1] << "): ";
        cout << particle.first << endl;
        io_queue.pop();
    }
}

void print_grid(const bool* grid, size_t n) {
    cout << "+";
    for (size_t i = 0; i < n; i++)
        cout << "-";
    cout << "+" << endl;
    for (size_t i = 0; i < n; i++) {
        cout << "|";
        for (size_t j = 0; j < n; j++)
            cout << (grid[i*n + j] ? 'x' : ' ');
        cout << "|" << endl;
    }
    cout << "+";
    for (size_t i = 0; i < n; i++)
        cout << "-";
    cout << "+" << endl;
}

void update_system(System& system, double& time) {
    auto particle = system.first.pop();
    time += particle.first;
    Coordinates *coords = particle.second;
}

int main(int argc, char *argv[]) {
    const int grid_size {10};
    size_t nr_particles = 10;
    if (argc > 1)
        nr_particles = stoi(string(argv[1]));
    auto engine {mt19937_64(1234)};
    auto pos_distr = bind(uniform_int_distribution<int>(0, grid_size - 1),
                          ref(engine));
    auto time_distr = bind(gamma_distribution<double>(3.0, 1.0),
                           ref(engine));
    System system = init_system(nr_particles, pos_distr, time_distr);
    print_queue(system.first);
    print_grid(system.second, grid_size);
    return 0;
}
