# Screen configuration

Having multiple windows that persist through sessions is a very nice
feature when working on various things simultaneously.  Simply dedicate a
screen session to each task, and you can resume at the point you left off
each time you switch context.


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
