# vi keybindings in the termial

By default, the terminal running bash support the Emacs keybindings, e.g.,
  * `ctrl-a` to move to the start of the input,
  * `ctrl-e` to move to the end of the input,
  * `alt-b` to move back a word,
  * `alt-f` to move forward a word, and so on.

However, this default behavior can be changed to vi keybindings, including
a command and an insert mode.  To get this to work, you need a file
named `.inputrc` in your home directory with the following contents.
```
set editing-mode vi
set keymap vi-command
```

The prompt starts in insert mode, so you can type as usual.  To switch to
command mode, hit `ESC`. Now many of the vi commands work, e.g.,
  * `^` to move to the start of the input,
  * `$` to move to the end of the input,
  * `b` to move backward a word,
  * `f` to move forward a word,
  * `\<search-string>` to search your history backward, and so on.

A conveniet [cheat sheet](http://www.catonmat.net/download/bash-vi-editing-mode-cheat-sheet.pdf) in PDF format is available.

It takes some getting used to, but will save you quite some keystrokes
at the end of the day.
