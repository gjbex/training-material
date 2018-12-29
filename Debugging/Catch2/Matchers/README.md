# Matchers

Catch2 support matchers in the `REQUIRE_THAT` macro.  Here are some
illustrations.

## What is it?

  1. `ip_address.cpp`: the function under test generates random IP4 addresses
    as a string.  The test case matches those against a regular expression.
