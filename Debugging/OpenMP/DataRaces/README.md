# DataRace
The code samples included illustrate some simple examples of data races.
They can be used to demo Intel Inspector.

## What is it?
1. `pi1.f90`: data races on `pi_sum`, `thread_num`, and `num_threads`
    variables.
1. `pi2.f90`: using `reduction` the data race on `pi_sum` has been
    eliminated, but the other errors are still present.
1. `pi3.f90`: all data races eliminated.  Note that the assumption is made
    that the schedule will be `static`.
1. `pi4.f90`: the schedule is set to `runtime` to allow illustrating how
    the assumption will lead to errors.
1. `pi5.f90`: version which is independent of the schedule used, and has
    no data races
1. `pi_classic.f90`: simple race condition, suited for demo.
1. `Makefile`: make file to build the code.
1. `drd_no_race_conditions.txt` and `drd_race_conditions.txt`: example DRD
    output.
1. `Scenarios`: scenarios for demonstrating Vlagrind and other tools.

## How to use?
To use Valgrind's Data Race Detector (DRD), run with the `--tool=drd`
option.  To check race conditions on stack variables, add the
`--check-stack-var=yes` option.
```bash
$ OMP_NUM_THREADS=2 valgrind --tool=drd --check-stack-var=yes ./pi1.exe
```
