#include <functional>
#include <iostream>
#include <random>

#include "particle.h"

using particle::Particle;

int main() {
    auto engine {std::mt19937_64(1234)};
    auto pos_distr = std::bind(std::uniform_real_distribution<double>(-1.0, 1.0),
                               std::ref(engine));
    auto mass_distr = std::bind(std::uniform_real_distribution<double>(0.0, 1.0),
                                std::ref(engine));
    Particle p1(pos_distr, mass_distr);
    Particle p2(pos_distr, mass_distr);
    std::cout << p1 << std::endl << p2 << std::endl;
    p1.move(0.5, 0.5, 0.5);
    std::cout << "moved: " << p1 << std::endl;
    std::cout << "x = " << p1.x() << ", y = " << p1.y() << ", z = " << p1.z()
              << std::endl;
    std::cout << "distance = " << p1.dist(p2) << std::endl;
    return 0;
}
