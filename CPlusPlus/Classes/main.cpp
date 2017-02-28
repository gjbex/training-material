#include <iostream>
#include "particle.h"

using namespace std;

int main(void) {
    Particle p(0.0, 0.0, 1.0, 0.5, 1.0);
    cout << p << endl;
    p.move(0.1);
    cout << p << endl;
    return 0;
}
