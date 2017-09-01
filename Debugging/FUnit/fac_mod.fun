test_suite fac_mod

test fac_0
    assert_equal(fac(0), 1)
end test

test fac_1
    assert_equal(fac(1), 1)
end test

test fac_4
    assert_equal(fac(4), 24)
end test

test fac_too_large
    integer(kind=8), parameter :: target = 6227020800
    assert_equal(fac(13), target)
end test

end test_suite
