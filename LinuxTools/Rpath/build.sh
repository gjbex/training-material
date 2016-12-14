#!/bin/bash

executable=say_hello.exe

cd Library && make && cd ..
if [ $? -ne 0 ]
then
    exit $?
fi
cd Library_alt && make && cd ..
if [ $? -ne 0 ]
then
    exit $?
fi
cd Application && make && cd ..
if [ $? -ne 0 ]
then
    exit $?
fi
cp Application/${executable} .
