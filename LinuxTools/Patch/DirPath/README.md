# DirPatch

Illustrationn of how to use patch on a directory.

## How to patch a single file?

1. The original directory is `orig`.  First, create a copy that
   `diff` will use as the original.
   ```bash
   $ cp -r orig orig_src
   ```
1. Create a modified version by editing files in the `orig`
   directory, and adding new directories and files.  For
    illustration purposes, an "edited" version can be copied from
     `orig_target.c`, so
   ```bash
   $ cp -r orig_target orig
   ```
1. Now we create a patch that can be used to make changes to `orig`.
   ```bash
   $ pushd orig
   $ diff  -Nrau  ../orig_src  .  >  ../orig.patch
   $ popd
   ```
   The `-a` flag tells `diff` to treat all files as text.
1. We can remove the modified directory since all changes are in
   the patch file.
   ```bash
   $ rm -r orig
   ```
1. The party that wan't to apply the patch typically has the original
   `orig` directory.  In the course of this example, we removed it
   though, so we copy it from `orig_src`.
   ```bash
   $ cp -r orig_src orig
   ```
1. Now the patch can be applied to `orig` which will be modified in place.
   ```bash
   $ pushd orig
   $ patch -p0 < ../orig.patch
   $ popd
   ```
1. The  patched `orig` directory is now the same as `orig_target`,
   verify using `diff`.
   ```bash
   $ diff -r orig orig_target
   ```
