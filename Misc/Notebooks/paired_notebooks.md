---
jupyter:
  jupytext:
    formats: ipynb,md
    text_representation:
      extension: .md
      format_name: markdown
      format_version: '1.0'
      jupytext_version: 1.0.0
  kernelspec:
    display_name: Python 3
    language: python
    name: python3
---

# Paired notebooks

```python
import matplotlib.pyplot as plt
%matplotlib inline
import numpy as np
```

```python
x = np.linspace(0.1, 3.0, 101)
y = np.log(x)
```

```python
_ = plt.plot(x, y)
```

```python
y = np.sqrt(x)
```

```python
_ = plt.plot(x, y)
_ = plt.xlabel('x')
_ = plt.ylabel('y')
```
