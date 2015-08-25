Executing external programs or shell commands
=============================================

Executing external programs or shell commands can conveniently be done
using Python's `subprocess` module in the standard library.  It allows
to send input to the external command (if necessary), and capture
what is sent to standard output and/or standard error by that command.
The exit code can also be retrieved.

What is it?
-----------
`wc_metrics.py`: this script computes the number of characters, words, and
lines in a file using the shell's `wc` commaand.

