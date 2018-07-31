# Some plotting examples

```python
import numpy as np
import matplotlib.pyplot as plt
```

First, let's prepare some data to use.  We create x-values ranging between -1.0
and 1.0.

```python
x = np.linspace(-1.0, 1.0, num=101)
```

Next, we compute the y-values, a simple sine will do, we implement $\sin 5\pi
x$.

```python
y = np.sin(5*np.pi*x)
```

We want plots to appear inline, so some matplotlib magic should do the trick.

```python
%matplotlib inline
```

Now we use matplotlib to plot y-values versus x-values.

```python
plt.plot(x, y);
```
