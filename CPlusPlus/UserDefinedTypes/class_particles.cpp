#include <cmath>
#include <functional>
#include <iostream>
#include <random>

using namespace std;

class Particle {
    private:
        double _x, _y, _z;
        double _mass;
        int _charge;
    public:
        Particle(function<double()> pos_distr,
                 function<double()> mass_distr,
                 function<int()> charge_distr) :
            _x {pos_distr()},
            _y {pos_distr()},
            _z {pos_distr()},
            _mass {mass_distr()},
            _charge {charge_distr() == 0 ? -1 : 1} {};
        double x() const { return _x; }
        double y() const { return _y; }
        double z() const { return _z; }
        double mass() const {return _mass; }
        double charge() const {return _charge; }
        void move(double dx, double dy, double dz);
        double dist(const Particle& other) const;
        double e_force(const Particle& other) const;
};

ostream& operator<<(ostream& out, const Particle& p);

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
    cout << "x = " << p1.x() << ", y = " << p1.y() << ", z = " << p1.z()
         << endl;
    cout << "distance = " << p1.dist(p2) << endl;
    cout << "force = " << p1.e_force(p2) << endl;
    return 0;
}

inline double sqr(double x) {
    return x*x;
}

void Particle::move(double dx, double dy, double dz) {
    _x += dx;
    _y += dy;
    _z += dz;
}

double Particle::dist(const Particle& other) const {
    return sqrt(sqr(_x - other.x()) + 
                sqr(_y - other.y()) +
                sqr(_z - other.z()));
}

double Particle::e_force(const Particle& other) const {
    const double q_e {1.6021e-19};
    const double k_c {8.98755e9};
    double r {dist(other)};
    return -k_c*charge()*other.charge()*sqr(q_e/r);
}

ostream& operator<<(ostream& out, const Particle& p) {
    return out << "(" << p.x() << ", " << p.y() << ", " << p.z() << ")"
               << ", mass = " << p.mass() << ", charge = " << p.charge();
}
