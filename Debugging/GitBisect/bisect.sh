#!/usr/bin/env bash

cd repo

# show compact git log for the repo
printf "\nlog entries:\n"
git log --oneline

# determine last and first commit, last commit is bad, first commit is
# good
bad_commit=$(git log --oneline | head -1 | cut -d ' ' -f 1)
good_commit=$(git log --oneline | tail -1 | cut -d ' ' -f 1)

printf "\nfirst good commit $good_commit -> last bad commit $bad_commit\n"

# start bisection
printf "\nstarting bisection...\n"
git bisect start $bad_commit $good_commit

# do bisection until the first bad commit is found
while true
do
    make test
    if [ $? -eq 0 ]
    then
        result=$(git bisect good)
    else
        result=$(git bisect bad)
    fi
    printf "\n$result"
    echo $result | grep 'is the first bad commit' &> /dev/null
    if [ $? -eq 0 ]
    then
        break
    fi
done

printf '\n\nFirst bad commit: '
git log --oneline | head -1

# stop bisection
printf "\nstop bisection...\n"
git bisect reset
