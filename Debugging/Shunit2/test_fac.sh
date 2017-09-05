#!/usr/bin/env bash

testFac0() {
    result=$(./fac.py 0)
    assertEquals 1 ${result}
}

testFac1() {
    result=$(./fac.py 1)
    assertEquals 1 ${result}
}

testFac5() {
    result=$(./fac.py 5)
    assertEquals 120 ${result}
}

testFacNegative() {
    err_file="${SHUNIT_TMPDIR}/err.txt"
    result=$(./fac.py -333 2> "${err_file}")
    exit_code=$?
# verify exit code
    assertEquals 1 ${exit_code}
# verity there is no output to stdout
    assertNull "${result}"
# verify error message on stderr
    assertEquals "### error: argument should be positive" \
                 "$(cat ${err_file})"
}

testFac4() {
    result=$(./fac.py 4)
    assertEquals "fails on purpose," 120 ${result}
}

source shunit2
