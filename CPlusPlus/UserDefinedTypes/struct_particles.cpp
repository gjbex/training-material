#include <cmath>
#include <functional>
#include <iostream>
#include <random>

using namespace std;

struct Particle {
    double x, y, z;
    double mass;
};

Particle init_particle(function<double()> pos_distr,
                       function<double()> mass_distr);
void move_particle(Particle& p, double dx, double dy, double dz);
double dist(const Particle& p1, const Particle& p2);
ostream& operator<<(ostream& out, const Particle& p);


int main() {
    auto engine {mt19937_64(1234)};
    auto pos_distr = bind(uniform_real_distribution<double>(-1.0, 1.0),
                          ref(engine));
    auto mass_distr = bind(uniform_real_distribution<double>(0.0, 1.0),
                           ref(engine));
    Particle p1 = init_particle(pos_distr, mass_distr);
    Particle p2 = init_particle(pos_distr, mass_distr);
    cout << p1 << endl << p2 << endl;
    move_particle(p1, 0.5, 0.5, 0.5);
    cout << "moved: " << p1 << endl;
    cout << "distance = " << dist(p1, p2) << endl;
    return 0;
}

double sqr(double x) {
    return x*x;
}

Particle init_particle(std::function<double()> pos_distr,
                       std::function<double()> mass_distr) {
    Particle p {
        .x = pos_distr(),
        .y = pos_distr(),
        .z = pos_distr(),
        .mass = mass_distr(),
    };
    return p;
}

void move_particle(Particle& p, double dx, double dy, double dz) {
    p.x += dx;
    p.y += dy;
    p.z += dz;
}

double dist(const Particle& p1, const Particle& p2) {
    return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y) + sqr(p1.z - p2.z));
}

ostream& operator<<(ostream& out, const Particle& p) {
    return out << "(" << p.x << ", " << p.y << ", " << p.z << ")"
               << ", mass = " << p.mass;
}
