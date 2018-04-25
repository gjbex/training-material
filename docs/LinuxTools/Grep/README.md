# grep tricks

`grep` is a very useful tool to search for lines of text that contain
(or don't contain) certain patterns.  A few simple tricks make it even
more useful.

  1. Sometimes it can be hard to spot the pattern you were looking for
    in `grep` output.  Using the `--color=auto` option will show the
    matches in red so that they catch your eye immediately.  You can
    add the following alias definition in your `.bashrc`:
    `alias grep='grep --color=auto'`
  1. Although you can use `grep` to search through source code, you
    probably shouldn't, since there is a better alternative:
    [ack](https://beyondgrep.com/).
