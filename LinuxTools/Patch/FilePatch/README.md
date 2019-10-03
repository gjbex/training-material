# FilePatch

Illustrationn of how to use patch on a single file.

## How to patch a single file?

1. The original file is `orig.c`.  Since it will be overwritten later, so copy it
   from "original" source `orig_src.c`.
   ```bash
   $ cp orig_src.c orig.c
   ```
1. Create a modified version by copying `orig.c` and editing it.
   For illustration purposes this can be copied from `orig_target.c`,
   so
   ```bash
   $ cp orig_target.c orig_mod.c
   ```
1. Now we create a patch that can be used to make changes to `orig.c` so
   that its contents will be `orig_mod.c`.
   ```bash
   $ diff -u orig.c orig_mod.c > orig.patch
   ```
1. We can remove the modified file since all changes are in the patch file.
   ```bash
   $ rm orig_mod.c
   ```
1. Now the patch can be applied to `orig.c` which will be modified in place.
   ```bash
   $ patch < orig.patch
   ```
1. The file `orig.c` is now the same as `orig_target.c`, verify using `diff`.
   ```bash
   $ diff orig.c orig_target.c
   ```
   
