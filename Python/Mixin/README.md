Mixin
=====

Mix-in is a rather useful technique ni object-oriented programming.  It
allows to implement functionality that will be common to several classes
to be isolated in its own class, and be mixed-in through multiple
inheritance.

What is it?
-----------
1. `shape.py`: base class for object that have a shape, only provides
   name functionality
2. `colored.py`: class without constructor, only implements setter and
   getter functions for a color attribute
3. `circle.py`: inherits from Shape and Colored, and defines properties
   of a circle in 2D
4. `driver.py`: script to illustrate class instantiation

