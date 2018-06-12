# Scenario: Fortran format specification oddities

This application times a naive matrix-matrix multiplication using
`CPU_TIME`, and reports a value that is an order of magnitude too large.

  1. `$ make clean all`
  1. `$ time ./matrix_multiply.exe`
  1. Note that the reported time is off by an order of magnitude.
  1. `$ vim matrix_multiply.f90`
  1. `$ gdb ./matrix_multiply.exe`
  1. `(gdb) b 19`
  1. `(gdb) b 31`
  1. `(gdb) r`
  1. `(gdb) p tic`
  1. `(gdb) c`
  1. `(gdb) p tic`
  1. `(gdb) p toc`
  1. `(gdb) p dt`
  1. `(gdb) n`
  1. `(gdb) n`
  1. `(gdb) edit matrix_multiply.f90:32`
  1. Change `1pes` to `e`
  1. `:w`
  1. `:make`
  1. `:q`
  1. `(gdb) r`
  1. `(gdb) n`
  1. `(gdb) n`
  1. Correct timing is now printed.
