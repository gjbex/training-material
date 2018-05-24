from math import isclose
import pytest

from distance import distance

def test_distance_okay():
    assert isclose(5.0, distance((0.0, 4.0), (3.0, 0.0)))

def test_distance_crash():
    assert isclose(1.0, distance(1.0, 2.0))
