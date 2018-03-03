# grep tricks

`grep` is a very useful tool to search for lines of text that contain
(or don't contain) certain patterns.  A few simple tricks make it even
more useful.

  1. Sometimes it can be hard to spot the pattern you were looking for
    in `grep` output.  Using the `--color` option will show the matches
    in red so that they catch your eye immediately.  You can add the
    following alias definition in your `.bashrc`:
    `alias grep='grep --color'
