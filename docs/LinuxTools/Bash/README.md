# Bash

Some tips and trick make using Bash a lot easier.

  1. Setting the [shell prompt](Ps1.md) to something more informative and
     getting a less crowded terminal as well.
  1. Of course you can use environment variables for paths to frequently
     used directory names in your `.bash_profile`, but bookmarking
     directories is a lot more convenient.
     [CDargs](http://www.skamphausen.de/cgi-bin/ska/CDargs) helps you to
     do just that.
      * Use `ca <bookmark>` to add the current working directory with
        label `<bookmark>`.
      * Use `cdb <bookmark>` to change the directory to `<bookmark>`.
      * Invoke the GUI for CDargs using `cv` (type `H` to get help).
  1. If you're really hard core, you can set your terminal to support
     [vi keybindings](vi_keybindings.md) rather than the default Emacs
     bindings.
