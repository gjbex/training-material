# Typing
Python 3.5 introducd optional type annotation for functions, and that
functionality was extended in Python 3.6.

The `mypy` static type checker can use this annotation to detect type
errors.

## What is it?
`. `correct.py`: code that has type annotations, and no type errors.
`. `incorrect_01.py`: code that has type annotations, and passes a string
    to a function that expects an `int`.
`. `incorrect_02.py`: code that has type annotations, and the result of a
    function that returns an `int` is assigned to a `str` variable.
`. `incorrect_03.py`: code that has type annotations, and the result of a
    function that returns an `int`, assigns it to a variable that is
    later used as a `str`.
`. `dict_correct.py`: code that counts the words in a text read from
    standard input.
`. `dict_incorrect.py`: code that counts the words in a text read from
    standard input.  The counts are subsequently normalized to `float`,
    which is a type error.
