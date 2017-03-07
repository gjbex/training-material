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

Particle_queue init_system(size_t n, function<int()> pos_distr,
                           function<double()> time_distr) {
    Particle_queue queue(cmp);
    for (size_t i = 0; i < n; i++) {
        double time {time_distr()};
        Coordinates *coords = new Coordinates({pos_distr(), pos_distr()});
        Particle particle(time, coords);
        queue.push(particle);
    }
    return queue;
}

void print_queue(const Particle_queue& queue) {
    Particle_queue io_queue = queue;
    while (!io_queue.empty()) {
        Particle particle = io_queue.top();
        Coordinates *coords = particle.second;
        cout << "(" << (*coords)[0] << ", " << (*coords)[1] << "): ";
        io_queue.pop();
    }
}

int main(int argc, char *argv[]) {
    size_t nr_particles = 10;
    if (argc > 1)
        nr_particles = stoi(string(argv[1]));
    auto engine {mt19937_64(1234)};
    auto pos_distr = bind(uniform_int_distribution<int>(-10, 10),
                          ref(engine));
    auto time_distr = bind(gamma_distribution<double>(1.0, 1.0),
                           ref(engine));
    Particle_queue system = init_system(nr_particles, pos_distr,
                                        time_distr);
    print_queue(system);
    print_queue(system);
    return 0;
}
