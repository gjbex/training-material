import pytest

@pytest.fixture
def long_list():
    return list(range(15))

@pytest.fixture(scope='module')
def short_list():
    return list(range(5))

def test_len(short_list, long_list):
    assert len(short_list) == 5
    assert len(long_list) == 15

def test_pop(short_list, long_list):
    popped = short_list.pop()
    assert popped == 4
    popped = long_list.pop()
    assert popped == 14

def test_len_again(short_list, long_list):
    assert len(long_list) == 15
    assert len(short_list) == 5
