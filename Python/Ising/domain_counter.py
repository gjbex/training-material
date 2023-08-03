#!/usr/bin/env python

import numpy as np


def compute_neighbouts(coord, size):
    neighbours = []
    if coord[0] >= 1:
        neighbours.append((coord[0] - 1, coord[1]))
    if coord[0] + 1 < size:
        neighbours.append((coord[0] + 1, coord[1]))
    if coord[1] >= 1:
        neighbours.append((coord[0], coord[1] - 1))
    if coord[1] + 1 < size:
        neighbours.append((coord[0], coord[1] + 1))
    return neighbours


def find_domain(ising, domains, cd, domain_nr):
    queue = [cd]
    domains[cd] = domain_nr
    while queue:
        cd = queue.pop()
        for nb in compute_neighbouts(cd, ising.N()):
            if domains[nb] == -1 and ising.s(*cd) == ising.s(*nb):
                domains[nb] = domain_nr
                queue.insert(0, nb)


def identify_domains(ising):
    domains = -np.ones((ising.N(), ising.N()), dtype=np.int32)
    domain_nr = 0
    for i in range(domains.shape[0]):
        for j in range(domains.shape[1]):
            if domains[i, j] == -1:
                find_domain(ising, domains, (i, j), domain_nr)
                domain_nr += 1
    return domains, domain_nr


def compute_domain_sizes(ising):
    domains, nr_domains = identify_domains(ising)
    domain_sizes = [0] * nr_domains
    for i in range(domains.shape[0]):
        for j in range(domains.shape[1]):
            domain_sizes[domains[i, j]] += 1
    return domain_sizes
