# Scenario: find cause of stack trashing using a watchpoint

Application computes the sum of an array containing the square root of
integers.  However, although the array contains the expected numbers,
the sum is -NaN.

  1. `$ make clean all`
  1. `$ ./array_bounds.exe`
  1. Sum is NaN, stack trashing detected.
  1. `$ vim array_bounds.c`
  1. `$ gdb ./array_bounds.exe`
  1. `(gdb) b 11`
  1. `(gdb) r`
  1. `(gdb) p a`
  1. Values as expected.
  1. `(gdb) p sum`
  1. Oops, NaN.
  1. `(gdb) b main`
  1. `(gdb) r`
  1. `(gdb) awatch sum`
  1. `(gdb) r`
  1. Halt on initializatin of sum, okay.
  1. `(gdb) c`
  1. Halt on line 10.
  1. `(gdb) p &sum`
  1. `(gdb) p &a[-1]`
  1. Hence stack trashing.
