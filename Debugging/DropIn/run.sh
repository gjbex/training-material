#!/bin/bash

make clean all
output_file='test.txt'
unset LD_LIBRARY_PATH
unset LD_PRELOAD

rm -f $output_file

echo ''
echo 'running linked version'
LD_LIBRARY_PATH=$(pwd) ./test_linked.exe

echo ''
echo 'running non-linked version'
./test_not_linked.exe
if [ -e $output_file ]
then
    echo 'output file created, removing...'
    rm $output_file
fi

echo ''
echo 'running non-linked version with LD_PRELOAD'
LD_PRELOAD=$(pwd)/libintercept.so ./test_not_linked.exe
