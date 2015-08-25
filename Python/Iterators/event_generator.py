#!/usr/bin/env python

from datetime import datetime, timedelta
from random import uniform


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

    def __next__(self):
        delta = int(uniform(self._min_delay, self._max_delay))
        start = self._start + timedelta(seconds=delta)
        delta = int(uniform(self._min_duration, self._max_duration))
        duration = timedelta(seconds=delta)
        self._start = start + duration
        return Event(self._name, start, duration)


def event_key(event):
    if event[2] == 'on':
        return (event[0], event[1], 0)
    else:
        return (event[0], event[1], 1)

if __name__ == '__main__':
    from argparse import ArgumentParser
    import sys

    def main():
        arg_parser = ArgumentParser(description='event log generator')
        arg_parser.add_argument('--events', default=['heating'], nargs='+',
                                help='event types')
        arg_parser.add_argument('--start', default='2014-01-01',
                                help='start date')
        arg_parser.add_argument('--stop', default='2014-01-02',
                                help='stop date')
        options = arg_parser.parse_args()
        start = datetime.strptime(options.start, '%Y-%m-%d')
        stop = datetime.strptime(options.stop, '%Y-%m-%d')
        event_list = []
        for event_type in options.events:
            for event in EventIter(event_type, start):
                if event.start < stop:
                    event_list.append(event.begin())
                    if event.stop < stop:
                        event_list.append(event.end())
                else:
                    break
        event_list.sort(key=event_key)
        for event in event_list:
            print('{0};{1} {2}'.format(str(event[0]), event[1], event[2]))

    status = main()
    sys.exit(status)
