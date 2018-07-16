# Coding best practices: reading material

A number of very simple things go a long way towards improving your code substantially. For good programmers, they are second nature, and you should strive to make them into a habit.

In this section, we will use the term function in a very broad sense, simply to keep the text easy to read. In the context of Fortran, a function refers to the program unit, and any procedure, either a function or a subroutine. It also refers to a method defined in a class. In the context of C++, we will use the term function for methods as well.

Similarly, we use the term variable for constants, and also for attributes of objects and classes.


## Format your code nicely

To quote Robert C. Martin, "Code formatting is about communication, and communication is the professional developer’s first order of business."

All programming languages have one or possible multiple conventions about how to format source code. For example, consistent indentation of code helps considerably to assess the structure of a function at a glance. For multi-level indentation, always use the same width, e.g., multiples of four spaces. The following examples illustrate this, the first for a Fortran function, the second for an equivalent C function.

```
INTEGER FUNCTION factorial(n)
    IMPLICIT NONE
    INTEGER, INTENT(IN) :: n
    INTEGER :: i
    factorial = 1
    DO i = 2, n
        factorial = factorial*i
    END DO
END FUNCTION factorial
```

```
int factorial(int) {
    int fac = 1;
    int i;
    for(i = 2; i <= n; ++i)
        fac *= i;
    return fac;
}
```

In the function definitions, the body is indented by one level, and the body of the loop construct is indented an additional level. However, both levels have exactly four spaces. With a single glance, the structure of the code is clear.

A point to mention about your development environment: use a font for your editor that makes code easy to read.  Some fonts make it hard to distinguish between '0' and 'O', or '1' and 'l', so picking a good one will save time and effort.  A nice example is [Source Code Pro](https://github.com/adobe-fonts/source-code-pro) developed by Adobe.


## Use language idioms

Linguists use the term "idiom" for an expression that is very specific to a certain language, and that can be translated literally to another. For instance, the English idiom "it is raining cats and dogs" would translate to "il pleut des cordes" in French.  The corresponding idiom in French is completely unrelated to its counterpart in English. Mastering idioms is one of the requirements for C1 certification, i.e., to be considered to have a proficiency close to that of native speakers.

We observe a similar phenomenon for programming languages. Some syntactic constructs are typical for a specific programming language, but, when translated one-to-one into another language, lead to code constructs that are unfamiliar to programmers that are proficient in that language.

The code fragments above illustrate for Fortran and C. Although you could write line 5 of the C function as below, you should nevertheless refrain from doing so, since the syntactic shorthand used in the code above is in fact idiomatic for C and C++.
```
        fac = fac*i;
```

Using idioms, i.e., expressions that are particular to a (programming) language, will make your code much easier to interpret correctly by programmers that are fluent in that language.


## Choose descriptive names

In a way, programming is story telling. The data are the protagonist in the story, and the functions are the actions they take, or what happens to them. Hence variable names should be nouns, and functions verbs. If a function returns a property, it should be phrased as a question.

Any editor worth its salt provides completion, so you can't argue in favour of short, but less descriptive names to save typing. A long, but descriptive name is just a tab character away.

Choosing descriptive names for variables and functions is another aspect that can make reading your code much easier. Consider the following pseudo-code fragment, and although I'll grant that it is something of a caricature, I've seen some in the wild that are not significantly better.
```
f = open(fn, 'r')
for i in f:
    x = get(i)
    if condition(x):
        a = compute(x)
        if a < 3.14:
            do_something(a)
f.close()
```

If you don't have a clue of what is supposed to happen here, join the club.  Of course, we can make some guesses here.  The number 3.14 suggests pi, so `a` is probably an angle (in radians), and `i` is most likely a line in a text file.

However, it is clear that this code doesn't tell a story, although it may (or may not) instruct the computer to do the right thing. Digging through the code, reading the definitions of `get`, `condition`, and `do_something` we could of course figure out what is supposed to happen here, but that would be slow and cumbersome.

The pseudo-code below should be far more easy to follow.
```
PI = 3.14
data_file = open(file_name, 'r')
for line in data_file:
    data = parse_line(line)
    if is_valid(data):
        avg_angle = compute_avg_angle(data)
        if avg_angle < PI:
            display_output(avg_angle)
data_file.close()
```

A key principle of good software design is that of the least surprise. Choosing appropriate names for our variables and functions helps a lot in this respect.


## Keep it *simple*

Ideally, code is simple.  A function should have two levels of indentation at most.  This is advice you'll find in the literature on general purpose programming. Although this is good advice, there are some caveats in the context of scientific computing.

However, the gist is clear: code is as simple as possible, but not simpler.

Even for scientific code, a function has no more lines of code than fit comfortably on your screen. It is all too easy to lose track of the semantics if you can't get an overview of the code. Remember, not everyone has the budget for a 5K monitor.

If you find yourself writing a very long code fragment, ask yourself whether that is atomic, or whether the task it represents can be broken up into subtasks. If so, and that is very likely, introduce new functions for those subtasks with descriptive names. This will make the narrative all the easier to understand.

A function should have a single purpose, i.e., you should design it to do one thing, and one thing only.


## Limit scope

Many programmers will declare all variables at the start of block, or even at the start of a function's implementation. This is a syntax requirement in C89 and Fortran.  However, C99 and C++ allow you to declare variables anywhere before their first use. Since the scope of a variable starts from its declaration, and extends throughout the block, that means it is in fact too wide.

The following C89 code fragment illustrates this.
```
long n, distrNr;
Particle *p;
int step;
for (n = 0; n < nrParticles; n++) {
    p = initParticle(&params);
    distrNr = 0;
    addPosition(distrs->distr[distrNr], p);
    for (step = 1; step <= maxSteps; step++) {
        move(p, &params);
        if (step % deltaSteps == 0)
            addPosition(distrs->distr[step/deltaSteps], p);
    }
    freeParticle(p);
}
```

The scope of the variables `p`, `distrNr`, and `step` that are used in the for-loop over the number of particles can be limited to the body of that for loop, since those variables are not used in the surrounding code.
```
long n;
for (n = 0; n < nrParticles; n++) {
    Particle *p = initParticle(&params);
    long distrNr = 0;
    int step;
    addPosition(distrs->distr[distrNr], p);
    for (step = 1; step <= maxSteps; step++) {
        move(p, &params);
        if (step % deltaSteps == 0)
            addPosition(distrs->distr[step/deltaSteps], p);
    }
    freeParticle(p);
}
```
When using C99, the scope of the loop control variables `n` and `step` can be reduced as well.
```
for (long n = 0; n < nrParticles; n++) {
    Particle *p = initParticle(&params);
    long distrNr = 0;
    addPosition(distrs->distr[distrNr], p);
    for (int step = 1; step <= maxSteps; step++) {
        move(p, &params);
        if (step % deltaSteps == 0)
            addPosition(distrs->distr[step/deltaSteps], p);
    }
    freeParticle(p);
}
```
Limiting the scope of declarations to a minimum reduce the probability of inadvertently using the variable, but it also improves code quality: the declaration of the variable is at the same location where the variable is first used, so the narrative is easier to follow.

In C++ this may even have performance benefits since a declaration may trigger a call to a potentially expensive constructor.

Fortran requires that variables are declared at the start of a compilation unit, i.e., `PROGRAM`, `FUNCTION`, `SUBROUTINE`, `MODULE`, but Fortran 2008 introduced the `BLOCK` statement in which local variables can be declared. Their scope doesn't extend beyond the `BLOCK`. Modern compilers support this Fortran 2008 feature.

Note that Fortran still allows variables to be implicitly typed, i.e., if you don't declare a variable explicitly, its type will be `INTEGER` if its starts with the characters `i` to `n`, otherwise its type will be `REAL`. Although that may seem convenient, it is also a source of bugs.  The following code fragment illustrates this.
```
DO i = 1, 10
    total = totl + 10.0
END DO
```
Since the variables were not declared explicitly, `i` is interpreted as `INTEGER` and `total` as `REAL`. However, the misspelled `totl` is also implicitly typed as `REAL`, initialized to `0.0`, and hence the value of `total` will be `10.0` when the iterations ends, rather than `100.0` as was intended. To avoid these problems caused by simple typos, use the `IMPLICIT NONE` statement before variable declarations in `PROGRAM`, `MODULE`, `FUNCTION`, `SUBROUTINE`, and `BLOCK`.
```
IMPLICIT NONE
INTEGER :: i
REAL :: total
DO i = 1, 10
    total = totl + 10.0
END DO
```

The compiler would give an error for the code fragment above since all variables have to be declared explicitly, and `totl` was not.

When developing multithreaded C/C++ programs using OpenMP, limiting the scope of variables to regions of the code that is executed in parallel makes those variables thread-private, hence reducing the risk of race conditions. We will discuss this in more detail in a later section.


## Be explicit about constants

If a variable's value is not supposed to change during the runtime of a program, declare it as a constant, so that the compiler will warn you if you inadvertently modify its value. In C/C++, use the `const` qualifier, in Fortran, use `PARAMETER`.

If arguments passed to function should be read-only, use `const` in C/C++ code, and `INTENT(IN)` in Fortran. Although Fortran doesn't require that you state the intent of arguments passed to procedures, it is nevertheless wise to do so. The compiler will catch at least some programming mistakes if you do.

However, this is not quite watertight, in fact, one can still change the value of a variable that is declared as a constant in C.  Compile and run the following program, and see what happens.
```
#include <stdio.h>

void do_mischief(int *n) {
    *n = 42;
}

int main(void) {
    const int n = 5;
    printf("originally, n = %d\n", n);
    do_mischief((int *) &n);
    printf("mischief accomplished, n = %d\n", n);
    return 0;
}
```

We will revisit this example in a later section.


## Control access

When defining classes in C++ and Fortran, some attention should be paid to accessibility of object attributes. An object's state is determined by its attributes' values, so allowing unrestricted access to these attributes may leave the object in an inconsistent state.
```
module stats_mod
    use, intrinsic :: iso_fortran_env, only : f8 => REAL64, i8 => INT64, &
                                              error_unit
    implicit none

    type :: stats_type
        real(kind=f8) :: sum = 0.0_f8
        integer(kind=i8) :: n = 0_i8
    contains
        procedure :: add
        procedure :: avg
    end type stats_type

contains

    type(stats_type) function new_stats()
        implicit none
        new_stats%sum = 0.0_f8
        new_stats%n = 0_i8
    end function new_stats

    subroutine add(stats, value)
        implicit none
        class(stats_type), intent(inout) :: stats
        real(kind=f8), intent(in) :: value
        stats%sum = stats%sum + value
        stats%n = stats%n + 1
    end subroutine add

    real(kind=f8) function avg(stats)
        implicit none
        class(stats_type), intent(in) :: stats
        if (stats%n == 0) then
            write(unit=error_unit, fmt='(A)') '### error: no data for avg'
            stop
        end if
        avg = stats%sum/stats%n
    end function avg

end module stats_mod
```

The state of a `stats_type` object is determined by both the `sum` and the `n` attribute. The definition above of the user defined type allows the object's attributes to be modified, so that the object's state can be inconsistent.
```
...
type(stats_type) :: stats = new_stats()
integer :: i
do i = 1, 10
    call stats%add(5.0_f8)
end do
stats%n = 5
print '(F5.1)', stats%avg()
...
```

The average of the values added to the `stats` object is supposed to be 5.0, however since we can and did modify `stats%n`, the code fragment above would print 10.0 instead.  The problem can be prevented easily by restricting access to the object attributes by making them private.
```
private
type, public :: stats_type
    private
    real(kind=f8) :: sum = 0.0_f8
    integer(kind=i8) :: n = 0_i8
contains
    procedure :: add
    procedure :: avg
end type stats_type

public :: new_stats
```

If you try to modify the values of the attributes `sum` and `n`, outside of the module's scope, the code will no longer compile.


## Variable initialization

Although Fortran doesn't require you to initialize variables, and will set `INTEGER` and `REAL` to zero for you, it is nevertheless good practice to always initialize variables explicitly. It makes your intent clear. Although C/C++ will likely produce nonsense results when you forget to initialize a variable, the compilers will typically let you get away with it. However, most compilers have optional flags that catch expressions involving uninitialized variables. We will discuss these and other compiler flags in a later section.

When initializing or, more generally, assigning a value to a variable that involves constants, your code will be easier to understand when those values indicate the intended type. For example, using `1.0` rather than `1` for floating point is more explicit. This may also avoid needless conversions. This also prevents arithmetic bugs since `1/2` will evaluate to `0` in C, C++ as well as Fortran.  Perhaps even more subtly, `1.25 + 1/2` will also evaluate to `1.25`, since the division will be computed using integer values, evaluating to `0`, which is subsequently converted to the floating point value `0.0`, and added to `1.25`.


## To comment or not to comment?

Comments should never be a substitute for code that is easy to understand. In almost all circumstances, if your code requires a comment without which it can not be understood, it can be rewritten to be more clear.

Obviously, there are exceptions to this rule. Sometimes we have no alternative but to sacrifices a clean coding style for performance, or we have to add an obscure line of code to prevent a problem caused by over-eager compilers.

If you need to add a comment, remember that it should be kept up-to-date with the code. All too often, we come across comments that are no longer accurate because the code has evolved, but the corresponding comment didn't. In such situations, the comment is harmful, since it can confuse us about the intentions of the developer, and at the least, it will cost us time to disambiguate.

The best strategy is to make sure that the code tells its own story, and requires no comments.

A common abuse of comments is to disable code fragments that are no longer required, but that you still want to preserve. This is bad practice. Such comments make reading the code more difficult, and take up valuable screen real estate.
Moreover, when you use a version control system such as git or subversion in your development process, you can delete with impunity, in the sure knowledge that you can easily retrieve previous versions of your files. If you don't use a version control system routinely, you really should. See the additional material section for some pointers to information and  tutorials.


## Stick to the standard

The official syntax and semantics of languages like C, C++ and Fortran is defined in official specifications. All compilers that claim compliance with these standards have to implement these specifications.

However, over the years, compiler developers have added extensions to the specifications. The Intel Fortran compiler for instance has a very long history that can trace its ancestry back to the DEC compiler, and implements quite a number of Fortran extensions. Similarly, the GCC C++ compiler supports some non-standard features.

It goes without saying that your code should not rely on such compiler specific extensions, even that compiler is mainstream, and widely available. There is no guarantee that future releases of that same compiler will still support the extension, and the only official information about that extension would be available in the compiler documentation, not always the most convenient source.

Moreover, that implies that even if your code compiles with a specific compiler, that doesn't mean it complies with the official language specification. An other compiler would simply generate error message for the same code, and would fail to compile it.

Using language extensions makes code harder to read. As a proficient programmer, you're still not necessarily familiar with language extensions, so you may interpret those constructs incorrectly.

Hence I'd encourage you strongly to strictly adhere to a specific language specification on.  For C there are three specification that are still relevant, C89, C99, and C11.  For C++ that would be C++11, and C++14.  The relevant specification for Fortran are those of 2003 and 2008. References to those specifications can be found in the section on additional material.
