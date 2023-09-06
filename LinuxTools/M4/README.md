M4
==

M4 is a macro processor with many features.  It can be used to fill out
a template file.

Contents
--------
1. `simple.m4`: a simple example of an M4 macro file.  It contains two
    variables, one is defined in a macro in this file, the other is
    specified on the command line when `me` is invoked.
1. `simple_process.sh`: Bash shell script that invokes `m4` on `simple.m4`.
1. `underscore.m4`: another simple example of an M4 macro file.  Here, the
   aim is to replace the part of the string `SOMETHING_ELSE` after the
   underscore only.  Since M4 has longest-match semantics when tokenizing
   text, it will not pick up on `ELSE` since it only considers the token
   `SOMETHING_ELSE`, which is not a macro variable.  The `format` function
   is the easiest solution here.
1. `underscore_process.sh`: Bash shell script that invokes `m4`.
