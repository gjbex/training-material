#!/usr/bin/env python

from operator import attrgetter
from itertools import groupby


class Person(object):

    def __init__(self, name, age, city):
        self._name = name
        self._age = age
        self._city = city

    @property
    def name(self):
        return self._name

    @property
    def age(self):
        return self._age

    @property
    def city(self):
        return self._city

    def __str__(self):
        fmt_str = '{name} ({age:d}) lives in {city}'
        return fmt_str.format(name=self.name, age=self.age, city=self.city)


if __name__ == '__main__':
    people = [
        Person('Mary', 35, 'Paris'),
        Person('John', 43, 'Brussels'),
        Person('Carol', 23, 'Brussels'),
        Person('Alice', 69, 'Brussels'),
        Person('Jo', 33, 'Paris'),
        Person('Bob', 37, 'Paris'),
        Person('Francis', 19, 'Brussels'),
        Person('Jeanne', 56, 'Paris')
    ]
    print('original list:')
    for city, local_people in groupby(people, key=attrgetter('city')):
        print(city)
        for person in local_people:
            print(person)
    print()
# itertools.groupby only groups consecutive iterator results that have the
# same key, the original data has to be sorted to perform a grouping of
# the entire data set
    print('ordered list:')
    sorted_people = sorted(people, key=attrgetter('city'))
    for city, local_people in groupby(sorted_people,
                                      key=attrgetter('city')):
        print(city)
        for person in local_people:
            print(person)
    print()
# without sorting the data first, the same effect can be achieved as
# follwos
    print('collected data:')
    city_groups = {}
    for city, local_people in groupby(people, key=attrgetter('city')):
        if city not in city_groups:
            city_groups[city] = []
        city_groups[city].extend(list(local_people))
    for city, local_people in city_groups.items():
        print(city)
        for person in local_people:
            print(person)
