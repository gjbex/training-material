#include <cmath>
#include <functional>
#include <iostream>
#include <random>

struct Particle {
    double x, y, z;
    double mass;
};

Particle init_particle(std::function<double()> pos_distr,
                       std::function<double()> mass_distr);
void move_particle(Particle& p, double dx, double dy, double dz);
double dist(const Particle& p1, const Particle& p2);
std::ostream& operator<<(std::ostream& out, const Particle& p);


int main() {
    std::mt19937_64 engine(1234);
    auto pos_distr = std::bind(std::uniform_real_distribution<double>(-1.0, 1.0),
                               std::ref(engine));
    auto mass_distr = std::bind(std::uniform_real_distribution<double>(0.0, 1.0),
                                std::ref(engine));
    Particle p1 = init_particle(pos_distr, mass_distr);
    Particle p2 = init_particle(pos_distr, mass_distr);
    std::cout << p1 << std::endl << p2 << std::endl;
    move_particle(p1, 0.5, 0.5, 0.5);
    std::cout << "moved: " << p1 << std::endl;
    std::cout << "distance = " << dist(p1, p2) << std::endl;
    return 0;
}

inline double sqr(double x) {
    return x*x;
}

Particle init_particle(std::function<double()> pos_distr,
                       std::function<double()> mass_distr) {
    Particle p { pos_distr(), pos_distr(), pos_distr(), mass_distr()};
    return p;
}

void move_particle(Particle& p, double dx, double dy, double dz) {
    p.x += dx;
    p.y += dy;
    p.z += dz;
}

double dist(const Particle& p1, const Particle& p2) {
    using std::sqrt;
    return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y) + sqr(p1.z - p2.z));
}

std::ostream& operator<<(std::ostream& out, const Particle& p) {
    return out << "(" << p.x << ", " << p.y << ", " << p.z << ")"
               << ", mass = " << p.mass;
}
