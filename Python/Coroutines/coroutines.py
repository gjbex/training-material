#!/usr/bin/env python


def my_printer():
    try:
        counter = 0
        while True:
            buffer = (yield)
            counter += 1
            print('{0:03d}: {1}'.format(counter, buffer))
    except GeneratorExit:
        pass


def main():
    coroutine = my_printer()
    next(coroutine)
    for i in range(26):
        str = chr(ord('A') + i)
        coroutine.send(str)
    coroutine.close()

if __name__ == '__main__':
    main()
