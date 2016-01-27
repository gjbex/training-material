# HelloWorld
Most trivial example of Cython code.

## What is it?
1. `hello_world.pyx`: code to be compiled using Cython.
1. `setup.py`: Python build script.
1. `build.sh`: Bash script to execute the Python setup script.
1. `say_hello.py`: script to load the compiled module.  Note that the code
    is executed upon import since no guard is in place.
