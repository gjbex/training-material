#!/usr/bin/env python

from operator import attrgetter
from typing import List


class Person:

    def __init__(self, name: str, age: int) -> None:
        self._name = name
        self._age = age

    @property
    def name(self) -> str:
        return self._name

    @property
    def age(self) -> int:
        return self._age

    def __repr__(self) -> str:
        return f'{self.name} is {self.age}'


def average_age(people: List[Person]) -> float:
    return sum(map(attrgetter('age'), people))/len(people)


if __name__ == '__main__':
    people: List[Person] = [Person('alice', 43), 'bob']
    people.append(Person('carol', '17'))
    for person in people:
        print(person)
    print(f'average age is {average_age(people)}')
