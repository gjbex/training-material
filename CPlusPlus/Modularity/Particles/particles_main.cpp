#include <functional>
#include <iostream>
#include <random>

#include "particle.h"

using namespace std;

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
