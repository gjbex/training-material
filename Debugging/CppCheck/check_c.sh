#!/usr/bin/env bash

cppcheck --quiet --enable=all --inconclusive \
         --suppress=missingIncludeSystem \
         --language=c --std=c89 --platform=unix64 $*
