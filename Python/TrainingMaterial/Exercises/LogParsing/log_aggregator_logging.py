#!/usr/bin/env python

def create_event(event_str):
    event_date, event_info = event_str.split(';')
    event_name, event_type = event_info.split(' ')
    return (datetime.strptime(event_date, '%Y-%m-%d %H:%M:%S'),
            event_name, event_type)

if __name__ == '__main__':
    
    from datetime import datetime
    import logging, sys

    logging.basicConfig(filename='error.log', filemode='w',
                        format='%(asctime)s:%(levelname)s:%(message)s')
    events = {}
    aggr = {}
    for line in sys.stdin:
        date, name, type = create_event(line.strip())
        if name in events:
            if type == 'off':
                if name in aggr:
                    aggr[name] += date - events[name]
                else:
                    aggr[name] = date - events[name]
                del events[name]
            else:
                logging.warn('{0} on twice at {1}'.format(name, date))
        elif type == 'on':
            events[name] = date
        else:
            logging.warn('{0} off without on at {1}'.format(name, date))
    for name, date in events.items():
        logging.warn('{0} on without off at {1}'.format(name, date))
    for name, value in aggr.items():
        print '{0}: {1}'.format(name, value)

