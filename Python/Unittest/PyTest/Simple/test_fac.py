from fac import fac

import pytest


def test_fac_3():
    assert fac(3) == 6

def test_fac_0():
    assert fac(0) == 1

def test_fac_1():
    assert fac(1) == 1

def test_fac_5():
    assert fac(5) == 120

def test_fac_negative():
    with pytest.raises(ValueError):
        _ = fac(-1)    
