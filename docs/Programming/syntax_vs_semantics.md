# Syntax versus semantics

"Syntax" and "semantics" are two terms we will use often in this course. Most of you are probably familiar with these concepts, but just to make sure, let's define them briefly.

The syntax of a programming language is its grammar, i.e., the rules the source code text must satisfy in order to be considered syntactically correct. Let's illustrate that with an example from natural language. The sentence "the dog barks" is syntactically correct, while "the dog bark" is not.

Semantics on the other hand has to do with meaning, or interpretation. Again drawing on natural language examples, the sentence "the dog spoke" is syntactically correct, but the semantics is wrong. Obviously, dogs do not speak, except in fairy tales. The sentence "the dog bars" is both syntactically and semantically correct.

The following code fragments would be syntactically incorrect.
```fortran
PROGRAM syntax_error
    IMPLICIT none
    USE, INTRINSIC :: iso_fortran_env, ONLY : output_unit
    WRITE (UNIT=output_unit, FMT='(A)') 'hello world'
END PROGRAM syntax_error
```
This Fortran program has a syntax error that is dutifully reported by the `gfortran` compiler as:
```bash
$ gfortran -c syntax_error.f90
syntax_error.f90:3.57:

    USE, INTRINSIC :: iso_fortran_env, ONLY : output_unit
                                                         1
syntax_error.f90:2.17:

    IMPLICIT none
                 2
Error: USE statement at (1) cannot follow IMPLICIT NONE statement at (2)
```

The following Fortran function defintion has a semantic error, although it is syntactically correct.
```fortran
INTEGER FUNCTION fac(n)
    IMPLICIT NONE
    INTEGER, INTENT(IN) :: n
    INTEGER :: i
    fac = 1
    DO i = 0, n
        fac = fac*i
    END DO
END FUNCTION fac
```
The code fragment above will be compiled without errors or even warnings, but the function will return zero when invoked, regardless of the argument passed to it.

This illustrates an important point: syntax errors are always caught by the compiler. Although having to fix syntax errors is a nuisance, it is relatively easy.
Most semantic errors are not caught by the compiler, so these are harder to spot, and more difficult to fix. Compilers do offer some help detecting certain classes of semantic error, as we'll see in the next section.
