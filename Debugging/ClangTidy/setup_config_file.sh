#!/usr/bin/env bash

clang-tidy -checks='read*' -list-checks > .clang-tidy
