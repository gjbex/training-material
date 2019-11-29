EvaluateCode
============

Python allows executino of Python source code at runtime.  Although this
is a powerful feature, it should be used with extreme care, since it can
give rise to serious security issues.

What is it?
-----------
1. `evaluate.py`: short example that reads a code fragment, evaluates it,
    and prints all values of variables defined in that code fragment.
    Only variables of type `int`, '`float`, `str`, `bool` and `list` will
    be printed.`
1. `source.py`: sample code to evaluate using `evaluate.py`.
1. `nasty.py`: sample code to illustrate that `exec` can be harmful; will
   delete `my_precious.txt`, which should be copied from `my_precious.orig`;
   to be evaluated by `evaluate.py`.
1. `my_precious.orig`: file to copy to `my_precious.txt`.
1. `fib.py`: definition of Fibonacci function.
1. `fac.py`: definition of the recursive permutation function.
1. `fac_iter.py`: definition of the iterative permutation function.
1. `exec.py`: script that illustrates various uses of `exec`.
