#!/usr/bin/env python

def my_printer():
    try:
        buffer = ''
        counter = 0
        while True:
            buffer += (yield)
            counter += 1
            print '{0:03d}: {1}'.format(counter, buffer)
            buffer = ''
    except GeneratorExit:
        pass

def main():
    coroutine = my_printer()
    coroutine.next()
    for i in xrange(26):
        str = chr(ord('A') + i)
        coroutine.send(str)
    coroutine.close()

if __name__ == '__main__':
    main()
