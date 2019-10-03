# DirPatch

Illustrationn of how to use patch on a directory.

## How to patch a single file?

1. The original directory is `orig`.  Since it will be overwritten
   later, we copy it from "original" directory `orig_src`.
   ```bash
   $ cp -r orig_src orig
   ```
1. Create a modified version by editing the file `orig.c`.  For illustration,
   this can be copied from `orig_target.c`, so
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
   
