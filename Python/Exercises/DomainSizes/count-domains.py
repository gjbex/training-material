#!/usr/bin/env python

import sys

def read_lattice():
    lattice = []
    for line in sys.stdin:
        lattice.append(line.strip())
    return lattice

def compute_neighbouts(coord, size):
    neighbours = []
    if coord[0] - 1 >= 0:
        neighbours.append((coord[0] - 1, coord[1]))
    if coord[0] + 1 < size:
        neighbours.append((coord[0] + 1, coord[1]))
    if coord[1] - 1 >= 0:
        neighbours.append((coord[0], coord[1] - 1))
    if coord[1] + 1 < size:
        neighbours.append((coord[0], coord[1] + 1))
    return neighbours

def find_domain(lattice, domains, cd, domain_nr):
    queue = [cd]
    domains[cd[0]][cd[1]] = domain_nr
    while len(queue) > 0:
        cd = queue.pop()
        for nb in compute_neighbouts(cd, len(lattice)):
            if domains[nb[0]][nb[1]] == -1 and lattice[cd[0]][cd[1]] == lattice[nb[0]][nb[1]]:
                domains[nb[0]][nb[1]] = domain_nr
                queue.insert(0, nb)

def identify_domains(lattice):
    domains = []
    for _ in xrange(len(lattice)):
        domains.append([-1] * len(lattice))
    domain_nr = 0
    for i in xrange(len(lattice)):
        for j in xrange(len(lattice)):
            if domains[i][j] == -1:
                find_domain(lattice, domains, (i, j), domain_nr)
                domain_nr += 1
    return domains, domain_nr

def compute_domain_sizes(domains, nr_domains):
    domain_sizes = [0] * nr_domains
    for i in xrange(len(domains)):
        for j in xrange(len(domains)):
            domain_sizes[domains[i][j]] += 1
    return domain_sizes

def compute_domain_size_distribution(domain_sizes):
    distribution = {}
    for domain_size in domain_sizes:
        if domain_size not in distribution:
            distribution[domain_size] = 0
        distribution[domain_size] += 1
    return distribution

def print_domains(domains):
    for row in domains:
        print ''.join(['{0:02d}'.format(x) for x in row])

def print_lattice(lattice):
    for row in lattice:
        print row
    
def main():
    lattice = read_lattice()
    domains, nr_domains = identify_domains(lattice)
    domain_sizes = compute_domain_sizes(domains, nr_domains)
    distribution = compute_domain_size_distribution(domain_sizes)
    print 'size,nr_domains'
    for size in distribution:
        print '{0},{1}'.format(size, distribution[size])
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)

