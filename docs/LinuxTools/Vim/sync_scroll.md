# Synchronous buffer scrolling in vim

vim can be used to scroll the contents of two files side by side.  A few
commands are useful in this context.

  1. `:vsp` or `Ctrl-w v` splits the window vertically, i.e., two panes
    are shown side-by-side.
  1. `:set nowrap` ensures that vim doesn't display wrapped lines.
    Although this is often conveninet, it may make comparing files line by
    line harder.
  1. `:set scrollbind` should be done for each of the panes you want
    to scroll in sync.
  1. `Ctrl-w h` moves to the left pane, `Ctrl-w l` moves to the
    right pane.  Switching to the next pane can be donw with `Ctrl-w w`.
  1. `:q` will close a pane.
