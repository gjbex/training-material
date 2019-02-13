# tmux configuration

Having multiple windows that persist through sessions is a very nice
feature when working on various things simultaneously.  Simply dedicate a
screen session to each task, and you can resume at the point you left off
each time you switch context. tmux is an alternative to screen that has a
number of extra features.

A good introduction to tmux can be found on
[HackerNoon](https://hackernoon.com/a-gentle-introduction-to-tmux-8d784c404340)

## tmux configuration

Below is a sample tmxu configuration file.   By default, tmux
will read `~/tmux.conf`, although you can specify an alternative when starting
tmux using the `-f` flag.

```
# remap prefix to Control + a
set -g prefix C-a
# bind 'C-a C-a' to type 'C-a'
bind C-a send-prefix
unbind C-b

# split panes using | and -
bind | split-window -h
bind _ split-window -v
unbind '"'
unbind %

# reload config file (change file location to your the
# tmux.conf you want to use)
bind r source-file ~/.tmux.conf

# set inactive/active window styles
set -g window-style 'fg=colour247,bg=colour236'
set -g window-active-style 'fg=colour250,bg=colour232'

#pane border
set -g pane-border-bg colour235
set -g pane-border-fg colour238
set -g pane-active-border-bg colour236
set -g pane-active-border-fg colour51

# use vi keyboard shortcuts in copy mode
setw -g mode-keys vi

# switch mouse support on
set -g mouse on
```
It sets the prefix to `C-a` which makes switching between tmux and screen less
of an issue.  It also redefines the default bindings for splitting a pane
vertically or horizontally since these are easier to remember.

# tmuxp: a tmux session manager

The tmuxp session manager lets you specify tmux sessions in YAML or JSON files
so you can easily start a session with one or more windows and your
favorite layout.  In each pane, one or more bash command can be executed to
initialize your working environment.

Below you'll see a sample session configuration file.

```
session_name: dev_py
windows:
- window_name: dev
  layout: main-vertical
  options:
      main-pane-width: 90
  panes:
    - shell_command:
        - vim
      focus: true
    - shell_command:
        - module load conda
        - source activate py37
        - clear
    - null
```

This defines a session `dev_py` with a single window, named `dev`.  The
main pane is vertical, and has a width of 90 characters (to accommodate a
vi mwindow with decoration and 80 character width).  In the main pane, `vim`
is started.  The second pane loads a module, sources a conda environmet for
Python development, anc clears the screen.  The third panel doesn't execute
commands.

The `vim` editor will take up the left half of the screen, while the right-top
pane will have a conda environment ready to execute Python scripts.  The
right-bottom window can be used to do some shell commands.

Session files stored in the `~/tmuxp/` directory can be loaded by name, So
if the file above is stored in that directory, you can load this session by
ty typing:
```
$ tmuxp load dev_py
```
