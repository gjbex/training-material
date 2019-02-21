#include <functional>
#include <iostream>

class Particle {
    private:
        double x_, y_, z_;
        double mass_;
    public:
        Particle(std::function<double()> pos_distr,
                 std::function<double()> mass_distr) :
            x_ {pos_distr()},
            y_ {pos_distr()},
            z_ {pos_distr()},
            mass_ {mass_distr()} {};
        double x() const { return x_; }
        double y() const { return y_; }
        double z() const { return z_; }
        double mass() const {return mass_; }
        void move(double dx, double dy, double dz);
        double dist(const Particle& other) const;
        friend std::ostream& operator<<(std::ostream& out, const Particle& p);
};
