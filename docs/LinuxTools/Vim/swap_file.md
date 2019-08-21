# vim swap files

By default, vim creates a swap file for each file you open.  By default,
This is in the same directory as the file you are editing.  When you
open, e.g., `hello.txt`, a hidden file `.hello.txt.swp` will be created
in that same directory.

This may be problematic when editing very large files (which you might
want to do using different tools anyway).

You can set a directory for storing swap files by adding the following
to your `.vimrc`:

```
set swapfile
set dir='/some/place/where/you/have/a/lot/of/space'
```

You can also disable the creation of backup and swap files (temporarily)
by adding the following lines to `.vimrc`:

```
set nobackup       "no backup files
set nowritebackup  "only in case you don't want a backup file while editing
set noswapfile     "no swap files
```

Don't forget to remove these lines once you're done editing that
large file.
