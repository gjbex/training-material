#include <iostream>

#include "diffusion_system.h"

int main() {
    const size_t nr_particles {10};
    const size_t grid_size {10};
    System system(nr_particles, grid_size);
    system.print_grid();
    system.print_queue();
    return 0;
}
