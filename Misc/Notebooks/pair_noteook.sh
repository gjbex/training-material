#!/usr/bin/env bash

if [[ $# -lt 1 ]]
then
    (>2& echo "### error: no notebook specified" )
    exit 1
fi

while [[ $@ ]]
do
    file=$1
    grep -e '.ipynb$' <<< "$file" &> /dev/null
    if [[ $? -eq 0 ]]
    then
        jupytext --set-formats ipynb,md --sync "$file"
    fi
    shift
done
