#!/usr/bin/env bash

cppcheck --quiet --enable=all --inconclusive \
         --suppress=missingIncludeSystem \
         --language=c++ --std=c++14 --platform=unix64 $*
