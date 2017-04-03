# Configurations
Configuration files for various Linux tools that show some useful, but
non-default settings.

## What is it?
1. `bash_prompt`: fragment that can either be source or pasted into a
    `.bashrc` file that defines a more sane prompt than the default.
    The most notable is that the actual prompt starts on a new line,
    making this very useful with deeply nested directories.
1. `screenrc`: screen is a full-screen window manager that multiplexes
    a physical terminal between several processes, allowing to detach
    and reattach sessions. This configuration file defines a status
    line at the bottom of the screen that shows the open windows, and
    highlights the one that is active.
1. `vimrc`: basic vim configuration file that set tab stops, replaces
    tab insert by spaces insert, configures backup files, sets
    auto-indent.

## Important note
To use most of the configuration files, they need to be placed in your
home directory, and be renamed to start with a `.`, e.g., `screenrc`
should be renamed to `.screenrc`.
