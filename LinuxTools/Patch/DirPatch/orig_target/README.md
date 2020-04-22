# Greetings application

This is a greetings application.  It will greet you.

## How to use it?

You can be greeted by either "hello" or "bye", depending on the command line
option, if non is specifed, it defaults to hello.

* Default:
  ```bash
  $ ./greetings John
  Hello John!
  ```
* With `-h`:
  ```bash
  $ ./greetings -h John
  Hello John!
  ```
* With `-b`:
  ```bash
  $ ./greetings -b John
  Bye John!
  ```
