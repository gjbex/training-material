#include <functional>
#include <iostream>

struct Particle {
    double x, y, z;
    double mass;
    int charge;
};

Particle init_particle(std::function<double()> pos_distr,
                       std::function<double()> mass_distr,
                       std::function<int()> charge_distr);
void move_particle(Particle& p, double dx, double dy, double dz);
double dist(const Particle& p1, const Particle& p2);
double e_force(const Particle& p1, const Particle& p2);
std::ostream& operator<<(std::ostream& out, const Particle& p);
