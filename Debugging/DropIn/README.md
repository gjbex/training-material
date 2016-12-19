# DropIn
Sometimes it is useful to replace a library function by a different
implementation for, e.g., debugging purposes.

## What is it?
1. `intercept.c`: a reimplementation of the standard C `fopen`,
    `fprintf` (well, actually `__fprint_chk`) and `fclose` fuctions.
1. `test.c`: a `main` function that simply opens a file for writing,
    prints some text, and closes the file.
1. `Makefile`: make file to produce a shared library `libintercep.so` that
    contains the reimplemented functions, `test_linked.exe` that is simply
    linked to that library, and `test_not_linked.exe` that is linked only
    against the standand `glibc`.
1. `run.sh`: Bash shell script that builds the software, runs
    `test_linked.exe`, `test_not_linked.exe`, and finally
    `test_not_linked.exe`, but with `libintercept.so` preloaded.

## Notes
Note that it is a particularly bad idea to export the `LD_PRELOAD`
variable in yuor shell script since, depending on what is being
preloaded, shell commands and other executables may crash horribly.  Hence,
always use:
```bash
$ LD_PRELOAD=/path_to_lib/libwhatever.so ./executable.exe
```
