#!/usr/bin/env python

import random, sys

nucleotides = 'ACGT'

ntax = int(sys.argv[1])
nchar = int(sys.argv[2])

print '#NEXUS'
print ''
print 'begin data;'
print '\tdimensions ntax={0:d} nchar={1:d};'.format(ntax, nchar)
print '\tformat datatype=dna missing=? gap=-;'
print '\tmatrix'
for tax_nr in xrange(1, ntax + 1):
    tax_name = 'H{0}'.format(tax_nr)
    dna = []
    for _ in xrange(nchar):
        dna.append(random.choice(nucleotides))
    print '\t{0}\t{1}'.format(tax_name, ''.join(dna))
print ''
print ';'
print 'end;'

