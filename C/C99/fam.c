#include <err.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double mass;
    int dims;
    double position[];
} Particle;

typedef struct {
    int nr_particles;
    Particle *particle[];
} System;

Particle *init_particle(int dims);
System *init_system(int nr_particles, int dims);
void free_system(System *system);
double total_mass(System *system);
void print_system(System *system);

int main(int argc, char *argv[]) {
    int dims = 2;
    int nr_particles = 5;
    if (argc > 1)
        dims = atoi(argv[1]);
    if (argc > 2)
        nr_particles = atoi(argv[2]);
    System *system = init_system(nr_particles, dims);
    print_system(system);
    printf("total mass = %lf\n", total_mass(system));
    free_system(system);
    return EXIT_SUCCESS;
}

Particle *init_particle(int dims) {
    Particle *particle = (Particle *) malloc(sizeof(Particle) +
                                             dims*sizeof(double));
    if (particle == NULL)
        errx(EXIT_FAILURE, "can't allocate particle");
    particle->mass = ((double) rand())/RAND_MAX;
    particle->dims = dims;
    for (int i = 0; i < dims; i++)
        particle->position[i] = ((double) rand())/RAND_MAX;
    return particle;
}

System *init_system(int nr_particles, int dims) {
    System *system = (System *) malloc(sizeof(System) +
                                       nr_particles*sizeof(Particle *));
    system->nr_particles = nr_particles;
    for (int i = 0; i < nr_particles; i++)
        system->particle[i] = init_particle(dims);
    return system;
}

double total_mass(System *system) {
    double sum = 0.0;
    for (int i = 0; i < system->nr_particles; i++)
        sum += system->particle[i]->mass;
    return sum;
}

void free_system(System *system) {
    for (int i = 0; i < system->nr_particles; i++)
        free(system->particle[i]);
    free(system);
}

void print_particle(Particle *particle) {
    printf("(");
    for (int i = 0; i < particle->dims; i++)
        printf("%lf%s", particle->position[i],
                i < particle->dims - 1 ? ", " : ")");
    printf(": %lf\n", particle->mass);
}

void print_system(System *system) {
    for (int i = 0; i < system->nr_particles; i++)
        print_particle(system->particle[i]); 
}
