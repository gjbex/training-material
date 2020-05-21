#!/usr/bin/env bash

source "repo_defs.sh"

# remove the repository if it exists
./make_clean.sh

# create repo
mkdir -p "$repo_dir"
cd "$repo_dir"
git init

# populate repo
cp -r ../files/* .

# stage and commit
git add .
git commit -m 'Initial commit'
