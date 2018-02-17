# `Screen`

According to its [website](https://www.gnu.org/software/screen/), screen is a
full-screen window manager that multiplexes a physical terminal between several processes, typically interactive shells.

That means you can have several interactive shells open within the same
terminal, and switch between them using key shortcuts.

The main advantage though is that you can disconnect from it, and reconnect at
some later point in time. For example, you are working at the office, using an
SSH connection to a server.  In the shell  running on that server, you use
`screen`. Now you disconnect, go home, log in to the server at work using SSH.
You can then reconnect to that session to find all your shells
exactly as you left them (assuming the server didn't reboot).

This is a very nice feature when working on various things simultaneously.
Simply dedicate a `screen` session to each task, and you can resume at the
point you left off each time you switch context.

This page is not on how to use screen, there are extensive tutorials on that,
e.g., the one by
[Jack Huckaby](https://www.rackaid.com/blog/linux-screen-tutorial-and-how-to/),
or a very brief one by
[Matt Cutts](https://www.mattcutts.com/blog/a-quick-tutorial-on-screen/).

What they don't mention though is a small addition to `screen`'s
configuration file `.screenrc` that makes it so much more useful.

```
# Turn off that annoying start up message
startup_message off

# Lots of lines in the scroll buffer
defscrollback 10000

# Window list at the bottom
hardstatus alwayslastline
hardstatus string "%{rw}%H%{wk}|%?%-Lw%?%{wb}%n*%f %t%?(%u)%?%{wk}%?%+Lw%?"

# Turn off pesky visual bell
vbell off
```

The most relevant lines set the `hardstatus`, i.e., the status information at
the bottom of the terminal that lists the current windows. With that active,
you can see at a glance which windows are active, rather than having to type
a command to list them.

Switching of the visual bell is also quite useful when using bash completion.
Otherwise screen will revert the screen colors each time you hit tab, and
there's more than one option.
