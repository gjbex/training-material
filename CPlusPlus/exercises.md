# Exercises
These are some exercises you can do as part of the C++ training.

## The basics (Chapter 1)

  1. Write a program that writes a greeting to standard output. When
    a command line argument is provided, e.g., `Bjarne`, the greeting
    should be `hello Bjarne!`, otherwise `hello world!`.
    ([Solution](Basics/hello.cpp))
  1. Write a program that reads from standard input, and interpretes a
    string as a name.  It will write a greeting to standard output,
    unless it reads `quit`, then it will print `Bye!`.
    ([Solution](Basics/talk.cpp))
  1. Write a program that computes the factorial function for a number
    specified on the command line.
    ([Solution](Basics/fac.cpp))
  1. Write a program that computes the greatest common divisor of
    two integers specified on the command line.
    ([Solution](Basics/gcd.cpp))
  1. Write a program that uses three functions to
      1. initialize an array of `double` with the square roots of 0.0 up
        to the array's length minus one;
      2.  print that array to standard output; and
      3. compute the sum of the array elements, which is printed by the
        program.
    ([Solution](Basics/arrays.cpp))
  1. Write a program that implements two functions, the first to swap
    the values of two `int` variables, the second to swap the values of
    two `double` variables.  Print the values before and after calling
    the functions.  Use function overloading.
    ([(Solution](Basics/swap.cpp))
  1. Write a program that reads x and y coordinates from standard input,
    it computes and writes the distance of the corresponding point with
    respect to the origin.
    ([Solution](Basics/col_dist.cpp))
  1. Write a program that reads integers from standard input, and computes
    the sum. It should ignore input lines that start with `#`.
    ([Solution](Basics/data_parser.cpp))


## User defined types (Chapter 2)

  1. Write a program that manipulates particles.  A particle has x, y and z
    coordinates, as well as mass. Write a function that returns a structure
    initialized to given coordinates and mass, i.e., "creates" a particle.
    Write a function that moves a particle a given distance in the x, y and
    z directions. Write a fnction that comnputes the Euclidean distance
    between two given particles. Overload the `<<` operator to generate
    a representation of a particle as `(<x>, <y>, <z>), mass = <mass>`.
    ([Solution](UserDefinedTypes/struct_particles.cpp))
  1. Represent the particles of the previous exercise as a class, the
    functions will be the constructor and methods respectively.
    ([Solution](UserDefinedTypes/class_particles.cpp))
  1. Extend the previous exercise so that particles can have a charge. The
    ckharge is represented as an `enum class`.
    ([Solution](UserDefinedTypes/charged_particles.cpp))
  1. Create a class that represents statistical information for a stream of
    data.  Once an object is created, data (`double` numbers) can be added
    one at the time.  At any time, the current average can be obtained.
    ([Solution](UserDefinedTypes/streaming_stats.cpp))


## Separate compilation and error handling (Chapter 3)

  1. Represent particles by a class as in the previous chapter, but split
    the code over three files, a header file with the class definition,
    a C++ source file with the class methods' definitions, and a C++
    source file that defines the `main` function. Write a make file to
    build the application.
    ([Solution](Modularity/Particles))
  1. Create a class that represents statistical information for a stream of
    data.  Once an object is created, data (`double` numbers) can be added
    one at the time.  At any time, the current average can be obtained.
    ([Solution](Modularity/Stats)),
  1. Write a program that gets an integer from the command line, checks
    whether it is positive, and computes the factorial function of it.
    Do proper error handling, i.e., generate an error if no value is
    specified on the command line, when the value specified doesn't
    represent an integer, and when the integer is negative.
    ([Solution](Modularity/fac.cpp))


## Classes (chapter 4)

  1. Represent static particles by a class as in the previous chapter.
    Next, use this class as a base class for particles that have a
    velocity. Add a `move` method to this class that overrides the one
    in the base class, taking only a single argument, the time delta
    during which the particle will move.
    ([Solution](Classes/Particles))
  1. Create a class that represents statistical information for a stream of
    data.  Objects of this class only compute the average.  Use this as
    a base class for a derived class that can also compute the standard 
    deviation
    ([Solution](Classes/Stats))
  1. Create an abstract base class that represent algorithms for
    computing the quadrature of functions. Create two dervied classes,
    the first implements Simpson's method, the other the Gauss method. The
    main function takes a command line argument specifying which method
    to use to compute the numerical integral of a function over an
    interval.
    ([Solution](Classes/Quadrature))
    

## Templates (and unctional programming interluddes) (chapter 5)

  1. Implement a template for a functions that will swap the valuss of
    two variables passed by reference for any type (both variables have
    the same type).
    ([Solution](Temaples/swap.cpp))
  1. Implement a template for a function that will compute the sum of its
    arguments, regardless of the number of arguments.
    ([Solution](Temaples/sum.cpp))
  1. Implement two classes for performing a quadrature algorithms on a
    function over an interval.  Both classes are unrelated, but implement
    a method `integrate` with the same signature. Write a template functino
    that performs the numerical integration of a given function using
    either algorithm for an increasing size of the integration interval
    e.g., `[-1.0, 1.0]` to `[-5.0, 5.0]` in increments of 1.0.
    ([Solution](Temaples/DuckTyping))
  1. Write a function that computes the Euclidean distance between two
    points in 3D.  The points are represented as a length 3 array. Use
    type alliasing to make the code easier to read.
    ([Solution](Templates/points.cpp))
  1. Implement a class that represents a function to compute the angle
    of a swininging pendulum as a function of time.  The constructor fixes
    the frequency.
    ([Solution](Templates/pendulum_func_obj.cpp))
  1. Write a program that implements a function with two arguments to
    compute the angle of a swininging pendulum.  The first is time, the
    second the pendulum's frequency.  Use `std::bind` to create a new
    function that has the time as a single argument. Print the values in
    the range `[0.0, 20.0]`.
    ([Solution](Templates/pendulum_bind.cpp))
  1. Write a program that implements a function with two arguments to
    compute the angle of a swininging pendulum.  The first is time, the
    second the pendulum's frequency.  Write a lambda function that has
    the time as a single argument. Print the values in the range
    `[0.0, 20.0]`.
    ([Solution](Templates/pendulum_bind.cpp))
