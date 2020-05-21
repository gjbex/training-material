#!/usr/bin/env bash

source "repo_defs.sh"

# create repo
cd "$repo_dir"

# create branch
git checkout -b feature/beautify

# first edit/commit
sed -i s/text/Text/ text1.txt
git commit -a -m 'Fix capitalization of text'

# second edit/commit
sed -i s/text/TEXT/ text2.txt
git commit -a -m 'Change capitalization of text'

# Third edit/commit
sed -i s/git/Git/ text*.txt
git commit -a -m 'Fix capitalization of git'
