#include <iostream>
#include "particle.h"

using namespace std;

int main(void) {
    StaticParticle p_s(0.0, 0.0, 1.0);
    cout << "static particle: " << p_s << endl;
    Particle p1(1.0, 0.0, 1.0, 0.5, 1.0);
    cout << "particle 1: " << p1 << endl;
    Particle p2(0.0, 1.0, 0.0, 0.5, 2.0);
    cout << "particle 2: " << p2 << endl;
    cout << p1 << endl;
    const double delta_t = 0.1;
    p1.move(delta_t);
    cout << "particle 1 moved during " << delta_t << ": " << p1 <<  endl;
    cout << "distance particle 1, static partice: "
         << p1.dist(p_s) << endl;
    cout << "distance particle 1, partice 2: "
         << p1.dist(p2) << endl;
    return 0;
}
