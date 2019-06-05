#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

struct Particle {
    double x, y, mass;
};

using namespace std;

vector<Particle> init_particles(size_t n);
ostream& operator<<(ostream& out, const Particle& particle);
bool mass_cmp(const Particle& p1, const Particle& p2);
bool dist_cmp(const Particle& p1, const Particle& p2);
double distance(const Particle& p);

int main() {
    const size_t n {5};
    vector<Particle> particles = init_particles(n);
    cout << "original:" << endl;
    for (const auto& particle: particles)
        cout << particle << endl;
    sort(particles.begin(), particles.end(), mass_cmp);
    cout << "sorted by mass:" << endl;
    for (const auto& particle: particles)
        cout << particle << endl;
    sort(particles.begin(), particles.end(), dist_cmp);
    cout << "sorted by distance from origin:" << endl;
    for (const auto& particle: particles)
        cout << particle << " at " << distance(particle) << endl;
    return 0;
}

vector<Particle> init_particles(size_t n) {
    vector<Particle> particles;
    mt19937_64 engine;
    auto pos_distr = bind(normal_distribution<double>(0.0, 1.0),
                          ref(engine));
    auto mass_distr = bind(uniform_real_distribution<double>(0.1, 1.0),
                           ref(engine));
    for (size_t i = 0; i < n; i++) {
        Particle particle {pos_distr(), pos_distr(), mass_distr()};
        particles.push_back(particle);
    }
    return particles;
}

ostream& operator<<(ostream& out, const Particle& particle) {
    return out << "(" << particle.x << ", " << particle.y << "): "
               << particle.mass;
}

bool mass_cmp(const Particle& p1, const Particle& p2) {
    return p1.mass < p2.mass;
}

double distance(const Particle& p) {
    return p.x*p.x + p.y*p.y;
}

bool dist_cmp(const Particle& p1, const Particle& p2) {
    return distance(p1) < distance(p2);
}

