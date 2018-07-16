# cdargs

[`cdargs`](http://www.skamphausen.de/cgi-bin/ska/CDargs) is a utility to
bookmark directories so that you can easily navigate the file system.

For most Linux systems, you can install it easily using your favorite
package manager.  If not, installation is quite easy, just follow the
instruction in the `INSTALL` file, included in the tarball you can
download.

## How to use it?

In order to invoke the GUI, use:
```bash
$ cv
```

To add a bookmark to the current working directory, do:
```bash
$ ca <bookmark>
```
where you should replace `<bookmark>` by the bookmark you want to use for this
directory.

To change to a bookmarked directory, use:
```bash
$ cdb <bookmark>
```

To copy a list of files to a bookmarked directory, use:
```bash
$ cpb <list-of-files> <bookmark>
```
