#!/bin/bash

m4 \
   --define SOMETHING='foo_bar'    \
   --define ELSE='bar_foo'         \
   underscore.m4
