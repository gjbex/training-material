#include <cmath>
#include <functional>
#include <iostream>
#include <random>

using namespace std;

struct Particle {
    double x, y, z;
    double mass;
    int charge;
};

Particle init_particle(function<double()> pos_distr,
                       function<double()> mass_distr,
                       function<int()> charge_distr);
void move_particle(Particle& p, double dx, double dy, double dz);
double dist(const Particle& p1, const Particle& p2);
double e_force(const Particle& p1, const Particle& p2);
ostream& operator<<(ostream& out, const Particle& p);


int main() {
    auto engine {mt19937_64(1234)};
    auto pos_distr = bind(uniform_real_distribution<double>(-1.0, 1.0),
                          ref(engine));
    auto mass_distr = bind(uniform_real_distribution<double>(0.0, 1.0),
                           ref(engine));
    auto charge_distr = bind(uniform_int_distribution<int>(0, 1),
                           ref(engine));
    Particle p1 = init_particle(pos_distr, mass_distr, charge_distr);
    Particle p2 = init_particle(pos_distr, mass_distr, charge_distr);
    cout << p1 << endl << p2 << endl;
    move_particle(p1, 0.5, 0.5, 0.5);
    cout << "moved: " << p1 << endl;
    cout << "distance = " << dist(p1, p2) << endl;
    cout << "force = " << e_force(p1, p2) << endl;
    return 0;
}

double sqr(double x) {
    return x*x;
}

Particle init_particle(std::function<double()> pos_distr,
                       std::function<double()> mass_distr,
                       std::function<int()> charge_distr) {
    Particle p {
        .x = pos_distr(),
        .y = pos_distr(),
        .z = pos_distr(),
        .mass = mass_distr(),
        .charge = charge_distr() == 0 ? -1 : 1
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

double e_force(const Particle& p1, const Particle& p2) {
    const double q_e {1.6021e-19};
    const double k_c {8.98755e9};
    double r {dist(p1, p2)};
    return -k_c*p1.charge*p2.charge*sqr(q_e/r);
}


ostream& operator<<(ostream& out, const Particle& p) {
    return out << "(" << p.x << ", " << p.y << ", " << p.z << ")"
               << ", mass = " << p.mass << ", charge = " << p.charge;
}
