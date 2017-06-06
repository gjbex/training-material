#!/usr/bin/env python

import schedule
import time


def print_event(event):
    time_str = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())
    print('{0}: {1}'.format(time_str, event['counter']))


def set_event(event):
    event['counter'] += 1

if __name__ == '__main__':
    event = {'counter': 0}
    schedule.every(2).seconds.do(print_event, event)
    schedule.every().seconds.do(set_event, event)
    while True:
        schedule.run_pending()
        time.sleep(0.5)
