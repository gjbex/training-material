#include <cmath>
#include <functional>
#include <iostream>
#include <random>

using namespace std;

class Particle {
    private:
        double _x, _y, _z;
        double _mass;
    public:
        Particle(function<double()> pos_distr,
                 function<double()> mass_distr) :
            _x {pos_distr()},
            _y {pos_distr()},
            _z {pos_distr()},
            _mass {mass_distr()} {};
        double x() const { return _x; }
        double y() const { return _y; }
        double z() const { return _z; }
        double mass() const {return _mass; }
        void move(double dx, double dy, double dz);
        double dist(const Particle& other) const;
};

ostream& operator<<(ostream& out, const Particle& p);

int main() {
    auto engine {mt19937_64(1234)};
    auto pos_distr = bind(uniform_real_distribution<double>(-1.0, 1.0),
                          ref(engine));
    auto mass_distr = bind(uniform_real_distribution<double>(0.0, 1.0),
                           ref(engine));
    Particle p1(pos_distr, mass_distr);
    Particle p2(pos_distr, mass_distr);
    cout << p1 << endl << p2 << endl;
    p1.move(0.5, 0.5, 0.5);
    cout << "moved: " << p1 << endl;
    cout << "x = " << p1.x() << ", y = " << p1.y() << ", z = " << p1.z()
         << endl;
    cout << "distance = " << p1.dist(p2) << endl;
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

ostream& operator<<(ostream& out, const Particle& p) {
    return out << "(" << p.x() << ", " << p.y() << ", " << p.z() << ")"
           << ", mass = " << p.mass();
}
