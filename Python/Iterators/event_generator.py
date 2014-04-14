#!/usr/bin/env python

class Event(object):

    def __init__(self, name, start, duration):
        self._name = name
        self._start = start
        self._duration = duration

    @property
    def name(self):
        return self._name

    @property
    def start(self):
        return self._start

    @property
    def stop(self):
        return self.start + self.duration

    @property
    def duration(self):
        return self._duration

    def begin(self):
        return (str(self.start), self.name, 'on')

    def end(self):
        return (str(self.start + self.duration), self.name, 'off')


from datetime import datetime, timedelta
from random import uniform

class EventIter(object):

    def __init__(self, name, start, min_delay=10, max_delay=3600,
                 min_duraion=60, max_duration=5*3600):
        self._name = name
        self._start = start
        self._min_delay = min_delay
        self._max_delay = max_delay
        self._min_duration = min_duraion
        self._max_duration = max_duration

    def __iter__(self):
        return self

    def next(self):
        start = self._start + timedelta(seconds=uniform(self._min_delay,
                                                        self._max_delay))
        duration = timedelta(seconds=uniform(self._min_duration,
                                             self._max_duration))
        self._start = start + duration
        return Event(self._name, start, duration)


if __name__ == '__main__':
    import argparse, sys

    def main():
        name = 'heater'
        start = datetime.strptime('2014-01-01', '%Y-%m-%d')
        stop = datetime.strptime('2014-01-03', '%Y-%m-%d')
        for event in EventIter(name, start):
            if event.start < stop:
                print event.begin()
                if event.stop < stop:
                    print event.end()
            else:
                break

    status = main()
    sys.exit(status)
