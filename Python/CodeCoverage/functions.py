def fac_r(n):
    if n < 2:
        return 1
    else:
        return n*fac_r(n - 1)

def fac_i(n):
    result = 1
    for i in range(2, n + 1):
        result *= i
    return result
