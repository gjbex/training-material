#!/usr/bin/env python

from Bio.Seq import MutableSeq
from Bio.Alphabet.IUPAC import IUPACUnambiguousDNA
import random, sys

if len(sys.argv) > 1:
    nr_nucl = int(sys.argv[1])
else:
    nr_nucl = 10
alphabet = IUPACUnambiguousDNA()
sequence = MutableSeq('', IUPACUnambiguousDNA())
for _ in xrange(nr_nucl):
    sequence.append(random.choice(alphabet.letters))
print sequence


