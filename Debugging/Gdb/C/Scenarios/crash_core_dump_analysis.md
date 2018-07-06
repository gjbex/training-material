# Scenario: analyze a core dump

Application `crash.exe` crashes, use a core dump to see where and why.

  1. `$ make clean all`
  1. `$ ./crash.exe`
  1. `$ ls`
  1. No core, set ulimit
  1. `$ ulimit -c 50000`
  1. `./crash.exe`
  1. `$ ls`
  1. `$ gdb ./creash.exe core`
  1. `(gdb) bt`
  1. `(gdb) frame 6`
  1. `(gdb) l`
  1. The same variable `a` is freed twice.
