#!/usr/bin/env python

from argparse import ArgumentParser
import json

def get_age(person):
    return person['age']

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute mean age of people '
                                            'in a JSON file')
    arg_parser.add_argument('file', help='JSON file to use')
    options = arg_parser.parse_args()
    people = json.load(open(options.file, 'r'))
    avg_age = 0.0
    for person in people:
        avg_age += get_age(person)
    avg_age /= len(people)
    print(f'average age = {avg_age:.2f}')
