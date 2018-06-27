# Top

`top` is a tool to interactively or in batch gather information on
processes that run on a system.  It has some rather neat features
that are not so well known.

Note that in the tips below, the commands are **case sensitive**.

  1. To select the column on which the processes are sorted, use
    `<` to go one column to the left, `>` to go a column to the
    right.  To highlight the column top currently sorts on, press
    `x` (press `x` again to deactivate highlighting). To reverse
    the sort order, press `R`.
  1. You can display additional fields besides the default ones,
    pressing `f` brings up a screen to select/deselect fields.
    Press space to select/deselect.
  1. A few useful fields that are not shown by default, but that
    can be quite useful are:
      * `nTH     = Number of Threads`
      * `P       = Last Used Cpu (SMP)`
      * `WCHAN   = Sleeping in Function`
  1. To see all threads of a process, press `H`.
  1. If you only want to see processes owned by a given user, press
    `u`, and enter the user at the prompt.  To exclude processes
    from a user, use `!`, e.g., to see all processes not owned by
    `root`, use `!root`.
  1. To search for a string in the screen, press `L`, and use `&`
    to find again.
  1. To filter the processes show, press either `o` or `O` (case
    insensitive/case sensitive) and enter a search criterion. To
    remove all filter criteria, press `=`. These are a few examples
    of filters you can apply:
      * `USER=vsc` will show the processes of users that have an ID
        containing the string 'vsc'.
      * `%MEM>0.5`: show processes that consume more than 0.5 % of
        the available memory.
  1. To change the delay time, i.e., the time between screen
    refreshes, press `d` and enter the time in seconds.
  1. To see summary information for cores, rather than the whole
    system, press `1`, to see summary information per socket, press
    `2`.  
  1. To save a configuration to disk, press `W`.  This file is
    `.toprc` in your home directory. 
