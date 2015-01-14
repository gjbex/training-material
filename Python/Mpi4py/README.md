Mpi4py
======

Distributed parallel programs can be developed using this library (not
in Python's starndard library, requires that an MPI library is installed).
It follows the MPI standard to some degree, but simplifies in many places,
making development easy, at the price of performace.
Not to be advised when interprocess communication is fine-grained with
respect to communication given (much) larger overhead when compared with
C/C++ or Fortran implementations.

What is it?
-----------
1. `ring.py`: implementation of a "token" send around a ring
2. `run_ring.sh`: Bash script illustrating how to run the program
3. `ring.pbs`: PBS script to run the ring program as a job
4. `round_about.py`: another ring type implementation
5. `exchange.py`: even ranks send, odd ranks receive, and vice versa
6. `mpi_count.py`: count amino acids in a long sequence, distributing
   the work over processes
7. `large_dna.txt`: example data file to use with `mpi_count.py`

