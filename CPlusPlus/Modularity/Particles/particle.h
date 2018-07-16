#include <functional>
#include <iostream>

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
        friend ostream& operator<<(ostream& out, const Particle& p);
};

