# Jupyter Notebooks

  1. MarkDown
      * text style markup (headers, italic, bold, inline code)
      * text elements (lists, long code fragments)
      * links & images
      * LaTeX
  1. Executing code
      * Embedding plots (`%matplotlib inline`)
      * reusing previous output (`_`)
  1. Magic
      * `%hist`, `%whos`, `%psearch`, `%timeit`, `%xdel`, `%store`, `%store -r`
      * extensions: `%load_ext`
        * `%autoreload`
  1. Executing notebooks in batch
      * `nbconvert`
  1. Notebooks & version control
      * notebook is JSON file
      * `nbconvert`
  1. Jupyter  notebooks for presentations
      * `nbconvert --to slides --post serve`
      * RISE
  1. Interactivity
      * how to use `ipywidgets`
  1. Using Bash from a Python notebook
      * `!` magic
      * `%script`, `%script --out` magic
      * `%env` for input values
  1. Interacting with R from a Python notebook
      * `rpy2.ipython` extension
      * `%R` and `%%R` magic, `%%R -i ... -o ...`
      * `%Rpush` and `%Rpull`
  1. Alternative Jupyter kernels
      * R
      * bash
  1. Running a notebook non-locally
      * on VSC clusters
      * [Binder](https://mybinder.org/)
      * [Google Colaboratory](https://colab.research.google.com/notebooks/welcome.ipynb#recent=true)
  1. JupyterLab
      * multiple views on notebook
      * console to running kernels
