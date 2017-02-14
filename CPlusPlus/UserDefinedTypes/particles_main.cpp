#include <functional>
#include <iostream>
#include <random>

#include "particles.h"

using namespace std;

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
    cout << "distance = " << dist(p1, p2) << endl;
    cout << "force = " << e_force(p1, p2) << endl;
    return 0;
}
