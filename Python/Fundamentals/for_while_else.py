#!/usr/bin/env python

print('for loop, normal termination')
for i in range(5):
    print('for {0}'.format(i))
else:
    print('else')

print('for loop, break')
for i in range(5):
    if i < 2:
        print('for {0}'.format(i))
    else:
        print('break {0}'.format(i))
        break
else:
    print('else')

print('while loop, normal termination')
i = 0
while i < 5:
    print('while {0}'.format(i))
    i += 1
else:
    print('else')

print('while loop, break')
i = 0
while i < 5:
    if i < 2:
        print('while {0}'.format(i))
        i += 1
    else:
        print('break {0}'.format(i))
        break
else:
    print('else')
