#!/usr/bin/env python


class CountDown(object):
    '''Class implementign a counter that goes from a start value to 0'''

    def __init__(self, n):
        '''Constructor setting the value to count down from'''
        self._n = n
        self._current = n

    @property
    def n(self):
        '''Returns value that this counter will count down frmo'''
        return self._n

    def __iter__(self):
        '''Initialize and return the iterator, this method is called
        each time the object is used as an iterator'''
        self._current = self.n
        return self

    def __next__(self):
        '''Returns the next value, and changes state, called in each
        iteration'''
        if self._current >= 0:
            value = self._current
            self._current -= 1
            return value
        else:
            raise StopIteration()

    def __str__(self):
        return 'count down at {c:d} from {n:d}'.format(self._current,
                                                       self.n)


if __name__ == '__main__':
    count_down = CountDown(5)
    print('first iteration')
    for i in count_down:
        print(i)
    print('second iteration')
    for i in count_down:
        print(i)
    for i in count_down:
        print(i)
    count_down1 = CountDown(10)
    count_down2 = CountDown(8)
    print('zip for 10, 8')
    for i, j in zip(count_down1, count_down2):
        print(i, j)
    print('zip for same iterator, will not work')
    for i, j in zip(count_down, count_down):
        print(i, j)
