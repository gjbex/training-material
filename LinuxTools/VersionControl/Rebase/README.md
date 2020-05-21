# Rebase

Squashing commits using interactive rebase can clean up history and ensure
that all commits in master build and pass tests.

## What is it?

1. `files`: some text files to use in the example scenario.
1. `repo_defs.sh`: defintion of the variables common to the Bash scripts.
1. `make_repo.sh`: create a git repository, populate it, and do initial commit.
1. `edit_files.sh`: create a branch, do some edit/commits.
1. `make_clean.sh`: remove the repository.

## Scenario

1. Run `make_repo.sh` to get the initial repository.
1. Run `edit_files.sh` to create a new branch, do some edits, followed by commits.
1. Change to the repository directory.
1. Run `git log` to view the commits, there are three in this branch.
1. Run `git rebase -i HEAD~3`, three commits with be displayed, all marked with
   `pick`.
1. Leave the first commit as is, change `pick` to `squash` for the remaiing two
   (in order shown in the edtior).
1. Quit the editor.
1. Edit the final commit message, and quit.
1. Run `git log` to show the new history.
1. Run `git reflog` to show that the history is still available.
1. Show one of the squashed commits using `git show <sha>`.
1. Optionally, cleanup using `make_clean.sh`.
