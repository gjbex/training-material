from fac import fac, bad_fac

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

def test_bad_fac_3():
    assert bad_fac(3) == 6

def test_bad_fac_0():
    assert bad_fac(0) == 1

def test_bad_fac_1():
    assert bad_fac(1) == 1

def test_bad_fac_5():
    assert bad_fac(5) == 120

def test_bad_fac_negative():
    with pytest.raises(ValueError):
        _ = bad_fac(-1)    
