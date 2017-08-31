#include <iostream>
#include "params.h"
#include "constrained_particles.h"
#include "particles.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "### error: " << argv[0] << " expects a "
                  << "configuration file" << std::endl;
        std::exit(1);
    }
    Params params;
    params.parse_file(argv[1]);
    params.dump();
    Particles *particles;
    if (params.constrained())
        particles = new Constrained_particles(params);
    else
        particles = new Particles(params);
    std::cout << "step,entropy" << std::endl;
    for (long step = 0; step <= params.maxSteps(); step++) {
        if (step % params.deltaSteps() == 0) {
            auto distr = particles->get_distribution();
            std::cout << step << ","
                      << distr.entropy() << std::endl;
        }
        particles->move();
    }
    delete particles;
    return 0;
}
