#!/usr/bin/env python

import math

def is_prime(n):
    for i in xrange(2, int(math.sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True
    
def next_prime():
    return (x for x in xrange(3, 2**31 - 1) if is_prime(x))

def main():
    for n in next_prime():
        print n
        if n > 1000:
            break

if __name__ == '__main__':
    main()

