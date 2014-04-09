#!/usr/bin/env python

from datetime import datetime
import sys

def parse_line(line):
    evt, evt_time = (x.strip() for x in line.split(':', 1))
    evt_type, evt_id = evt.split()
    return evt_type, evt_id, evt_time

def main():
    status = 0
    evt_starts = {}
    for line in sys.stdin:
        if len(line.strip()) == 0:
            continue
        evt_type, evt_id, evt_time = parse_line(line)
        if evt_type == 'start':
            if evt_id in evt_starts:
                sys.stderr.write('### error: multiple starts for {0}\n'.format(evt_id))
                status = 1
            evt_starts[evt_id] = datetime.strptime(evt_time,
                                                   '%Y-%m-%d %H:%M:%S')
        elif evt_type == 'end':
            if evt_id not in evt_starts:
                sys.stderr.write('### error: end without start for {0}\n'.format(evt_id))
                status = 2
            else:
                duration = datetime.strptime(evt_time,
                                             '%Y-%m-%d %H:%M:%S') - evt_starts[evt_id]
                print '{0}: {1}'.format(evt_id, str(duration))
    return status

if __name__ == '__main__':
    status = main()
    sys.exit(status)

