# Biopython
Biopython is the de facto standard to handle biological sequence data
and perfrm various bioinformatics computations.

## What is it?
1. `read_seq.py`: read a seqeunce file, e.g., in FASTA format, and
    compute some statistics on the sequences.
1. `align_seqs.py`: read a sequence file with multiple sequencs in,
    e.g., FASTA format, and perform a multiple alightment using MUSCLE.
1. `entrez_db_info.py`: search for Entrez database properties.
1. `UnalignedSeq14666.fasta`: sample FASTA format file containing multiple
    sequences.
1. `search_entrez.py`: search the NCBI Entrez nucleotide database for
    sequences of the MLH1 gene in homo sapiens by default, or any gene and
    organism specified via the command line.

## Requirements
The Biopython library should be installed, and, to run the `align_seqs.py`
script, the MUSCLE multiple alignment software tool as well
(http://www.drive5.com/muscle/).

## Note
The Entrez search script `search_entrez.py` queries the NCBI online
database, don't stress that database unnecessarily with this or
similar scripts.
