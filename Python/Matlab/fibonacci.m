function f = fibonacci(n)
    if n < 2
        f = int64(1);
    else
        f = int64(fibonacci(n - 1)) + int64(fibonacci(n - 2));
    end
end