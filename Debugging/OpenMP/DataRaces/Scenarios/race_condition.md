# Scenario: race condition in OpenMP application

The application derives the value of pi by computing a quadrature. The
integration domain is split up, and computed by OpenMP threads.  The
approximation is reasonable for 1 thread, but very bad for multiple
threads.

  1. `$ make clean all`
  1. `$ OMP_NUM_THREADS=1 ./pi_classic.exe`
  1. At least the three leading digits are correct.
  1. `$ OMP_NUM_THREADS=2 ./pi_classic.exe`
  1. The result is obviously wrong, use valgrind's DRD to detect data
    races.
  1. `$ valgrind --tool=drd --check-stack-var=yes ./pi_classic.exe |& less`
  1. DRD shows a problem on line 19 of `pi_classic.f90`.
