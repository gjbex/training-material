#include <cmath>
#include <functional>
#include <iostream>
#include <random>

using namespace std;

class Particle {
    private:
        double x, y, z;
        double mass;
        int charge;
    public:
        Particle(function<double()> pos_distr,
                 function<double()> mass_distr,
                 function<int()> charge_distr) :
            x {pos_distr()},
            y {pos_distr()},
            z {pos_distr()},
            mass {mass_distr()},
            charge {charge_distr() == 0 ? -1 : 1} {};
        void move(double dx, double dy, double dz);
        double dist(const Particle& other);
        double e_force(const Particle& other);
        friend ostream& operator<<(ostream& out, const Particle& p);
};


int main() {
    auto engine {mt19937_64(1234)};
    auto pos_distr = bind(uniform_real_distribution<double>(-1.0, 1.0),
                          ref(engine));
    auto mass_distr = bind(uniform_real_distribution<double>(0.0, 1.0),
                           ref(engine));
    auto charge_distr = bind(uniform_int_distribution<int>(0, 1),
                           ref(engine));
    Particle p1(pos_distr, mass_distr, charge_distr);
    Particle p2(pos_distr, mass_distr, charge_distr);
    cout << p1 << endl << p2 << endl;
    p1.move(0.5, 0.5, 0.5);
    cout << "moved: " << p1 << endl;
    cout << "distance = " << p1.dist(p2) << endl;
    cout << "force = " << p1.e_force(p2) << endl;
    return 0;
}

double sqr(double x) {
    return x*x;
}

void Particle::move(double dx, double dy, double dz) {
    x += dx;
    y += dy;
    z += dz;
}

double Particle::dist(const Particle& other) {
    return sqrt(sqr(x - other.x) + 
                sqr(y - other.y) +
                sqr(z - other.z));
}

double Particle::e_force(const Particle& other) {
    const double q_e {1.6021e-19};
    const double k_c {8.98755e9};
    double r {dist(other)};
    return -k_c*charge*other.charge*sqr(q_e/r);
}

ostream& operator<<(ostream& out, const Particle& p) {
    return out << "(" << p.x << ", " << p.y << ", " << p.z << ")"
               << ", mass = " << p.mass << ", charge = " << p.charge;
}
