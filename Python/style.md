Common problems & best practices
================================

This document is the result of code reviews and observations in the field.
Although there are quite some style guides for Python, it may perhaps
be useful to some anyway.  It is of course work in progress.

Useful references:
* Idioms and anti-idioms in Python:
    http://docs.python.org/2/howto/doanddont.html
* PEP 8:
    http://www.python.org/dev/peps/pep-0008/
* Google:
    http://google-styleguide.googlecode.com/svn/trunk/pyguide.html

Useful tools:
* Pylint, a syntax checker, static analyser and code style checker for
    Python: http://www.pylint.org/


Control flow
------------
When tempted to use `pass` in the body of a conditional statement, and
have only statements that do actual work in the `else` part, simply
use the negation of the condition, and dropt the `else`, e.g.,
```python
if x < 10:
    pass
else:
    total += x
```
is better replaced by:
```python
if x >= 10:
    total += x
```

A construct such as:
```python
for i in xrange(len(x)):
    f(x[i], y[i])
```
can be replaced by:
```python
for x_elem, y_elem in zip(x, y):
    f(x_elem, y_elem)
```


Regular expressions
-------------------
When a regular expression is compiled, an object is created with
its own methods, e.g., `search`, so
```python
import re
reg_expr = re.compile(r'\d+')
...
if reg_expr.search(some_str):
    ...
```
rather than
```python
reg_expr = re.compile(r'\d+')
...
if re.search(reg_expr, some_str):
    ...
```

Note the distiction between `search` and `match`: the former matches
at any point in the target stting, the latter only at the beginning of
the target string.


Files and I/O
-------------
When a file is opened in a `with` statement, i.e., under control of a
context manager, one need not explicitely close the file, since this
is handled by the context manager.


Data structures
---------------
When a list as a data structure where the items have non-homogeneous
types, especially lists or tuples, it is probably wise to consider
introducing a class to make code more robust, and easier to read and
hence maintain.


Data structures
---------------
To add all eleemnt of a list `b` to list `a`, do not use:
```python
for x in b:
    a.append(x)
```
but rather:
```python
a.extend(b)
```
Similarly, to add/update all key/value pair of a dictionary `b` to a
dictionary `a`, don not use:
```python
for key in b:
    a[k] = b[k]
```
but rater use:
```python
a.update(b)
```
The set data type has an `update` method with similar semantics.


String formatting
-----------------
It is always better to resist the temptation of using positional
substitution when using `format`, i.e., better replace:
```python
file_name = '{0}.txt'.format(base_Name)
```
by:
```python
file_name = '{base}.txt'.format(base=base_Name)
```

It is of course possible to create format strings programmatically, e.g.,
```python
for suffix in ['txt', 'csv']:
    file_tmpl = '{{base}}.{suffix}'.format(suffix=suffix)
    for basename in basenames:
        file_name = file_tmpl.format(base=basename)
        ...
```

Instead of:
```python
data_str = '{0}\t{1}\t{2}\t{3}'.format(itme1, item2, item3, item4)
```
consider:
```python
data_str = '\t'.join([itme1, item2, item3, item4])
```
