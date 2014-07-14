ConfigParser
============

ConfigParser is a module in Python's standard library to handle
configuration files easily.

What is it?
-----------
1. `config_reader.py`: reads a configuration file provided on the command
   line, or `default.conf`.  It prints the sections of the configuration
   files, and the key/value pairs defined therein.
2. `default.conf`: a configuration file with two sections (`physics` and
   `meta-info`, each defining two values.
3. `test.conf`: a configuration file to experiment with key names
   (case insensitive).
