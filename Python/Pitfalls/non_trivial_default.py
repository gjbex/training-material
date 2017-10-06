#!/usr/bin/env python

def filter(new_values, values=[]):
    for new_value in new_values:
        if new_value > 0:
            values.append(new_value)
    return values

if __name__ == '__main__':
    value_list = [
        [1, -3, 5],
        [13, 33, -15],
    ]
    for values in value_list:
        print(f'filtering {values}')
        filtered_values = filter(values)
        print(f'filtered: {filtered_values}')
