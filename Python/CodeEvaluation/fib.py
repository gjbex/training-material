def fib(n):
    return 1 if n in [0, 1] else fib(n-1) + fib(n-2)
