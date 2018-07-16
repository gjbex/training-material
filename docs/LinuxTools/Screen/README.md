# Screen

According to its [website](https://www.gnu.org/software/screen/), screen
is a full-screen window manager that multiplexes a physical terminal
between several processes, typically interactive shells.

That means you can have several interactive shells open within the same
terminal, and switch between them using key shortcuts.

The main advantage though is that you can disconnect from it, and reconnect
at some later point in time. For example, you are working at the office,
using an SSH connection to a server.  In the shell  running on that server,
you use screen. Now you disconnect, go home, log in to the server at work
using SSH.  You can then reconnect to that session to find all your shells
exactly as you left them (assuming the server didn't reboot).

This page is not on how to use screen, there are extensive tutorials on
that, e.g., the one by
[Jack Huckaby](https://www.rackaid.com/blog/linux-screen-tutorial-and-how-to/),
or a very brief one by
[Matt Cutts](https://www.mattcutts.com/blog/a-quick-tutorial-on-screen/).

Some tips and trick make using screen a lot easier though.

  1. Use [`.screenrc`](screenrc.md) to make your life easier, and be more
     productive when using screen.
