#!/usr/bin/env python

import random, sys

nucleotides = 'ACGT'

ntax = int(sys.argv[1])
nchar = int(sys.argv[2])
mut_prob = float(sys.argv[3])

init_seq = []
for _ in xrange(nchar):
    init_seq.append(random.choice(nucleotides))

print '#NEXUS'
print ''
print 'begin data;'
print '\tdimensions ntax={0:d} nchar={1:d};'.format(ntax, nchar)
print '\tformat datatype=dna missing=? gap=-;'
print '\tmatrix'
for tax_nr in xrange(1, ntax + 1):
    tax_name = 'H{0}'.format(tax_nr)
    dna = []
    for i in xrange(nchar):
        if random.random() < mut_prob:
            dna.append(random.choice(nucleotides))
        else:
            dna.append(init_seq[i])
    print '\t{0}\t{1}'.format(tax_name, ''.join(dna))
print ''
print ';'
print 'end;'


